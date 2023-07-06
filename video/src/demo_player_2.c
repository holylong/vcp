#include <stdio.h>
#include "libavcodec/avcodec.h"
#include "libavdevice/avdevice.h"
#include "libavformat/avformat.h"
#include "libswscale/swscale.h"
#include "libavutil/imgutils.h"
#include "SDL2/SDL.h"

/** 最新版本avcodec_decode_video2()接口已经废弃
 * 该接口功能分成avcodec_send_packet()和avcodec_receive_frame()两步实现
 * 以下代码根据这两个接口，重新实现avcodec_decode_video2()，以便后面代码调用
 */
// static int avcodec_decode_video2(AVCodecContext *avctx, AVFrame *frame, int *got_frame, AVPacket *pkt)
// {
//     int ret;

//     *got_frame = 0;

//     if (pkt) {
//         ret = avcodec_send_packet(avctx, pkt); // 发送编码数据包
//         // In particular, we don't expect AVERROR(EAGAIN), because we read all
//         // decoded frames with avcodec_receive_frame() until done.
//         if (ret < 0 && ret != AVERROR_EOF)
//             return ret;
//     }

//     ret = avcodec_receive_frame(avctx, frame); //接收解码后数据
//     if (ret < 0 && ret != AVERROR(EAGAIN))
//         return ret;
//     if (ret >= 0)
//         *got_frame = 1;

//     return 0;
// }

int main(int argc, char *argv[]) {
    AVFormatContext *pFormatCtx;
    AVCodecContext  *pCodecCtx;
    AVCodec         *pCodec;
    AVPacket        *packet;
    AVFrame         *pFrame,*pFrameYUV;

    // 视频文件放在项目路径里面
    // char filepath[] = "src01_480x272_22.h265";
//    char filepath[] = "test.mp4";

    const char *filepath = argv[1];

    unsigned char *out_buffer;
    struct SwsContext *img_convert_ctx;
    int i;
    int videoindex = -1;
    int ret;
    int got_picture;

    //SDL---------------------------
    int screen_w = 0;
    int screen_h = 0;
    SDL_Window *screen;
    SDL_Renderer* sdlRenderer;
    SDL_Texture* sdlTexture;
    SDL_Rect sdlRect;

    // 1.注册输入/输出设备
    avdevice_register_all();
    // 2.执行网络库的全局初始化（可选）
    avformat_network_init();
    pFormatCtx = avformat_alloc_context();

    // 3.打开流媒体
    if (avformat_open_input(&pFormatCtx, filepath, NULL, NULL) != 0) {
        printf("Couldn't open input stream.\n");
        return -1;
    }

    // 4.获取更多的码流信息
    if (avformat_find_stream_info(pFormatCtx, NULL) < 0) {
        printf("Couldn't find stream information.\n");
        return -1;
    }

    // 5.获取视频流的id
    for (i = 0; i < pFormatCtx->nb_streams; i++) {
        if(pFormatCtx->streams[i]->codecpar->codec_type == AVMEDIA_TYPE_VIDEO){
            videoindex = i;
            break;
        }
    }

    if (videoindex == -1) {
        printf("Didn't find a video stream.\n");
        return -1;
    }

    pCodecCtx = avcodec_alloc_context3(NULL);
    if (!pCodecCtx)
        return AVERROR(ENOMEM);

    // 6.将音频流信息拷贝到新的AVCodecContext结构体中
    ret = avcodec_parameters_to_context(pCodecCtx, pFormatCtx->streams[i]->codecpar);
    if (ret < 0)
        return -1;

    // 7.通codecId来查找解码器
    pCodec=avcodec_find_decoder(pCodecCtx->codec_id);
    if (pCodec == NULL) {
        printf("Codec not found.\n");
        return -1;
    }

    // 8.打开编解码器
    if (avcodec_open2(pCodecCtx, pCodec,NULL) < 0) {
        printf("Could not open codec.\n");
        return -1;
    }

    pFrame = av_frame_alloc();
    pFrameYUV = av_frame_alloc();
    out_buffer = (unsigned char *)av_malloc(av_image_get_buffer_size(AV_PIX_FMT_YUV420P, pCodecCtx->width, pCodecCtx->height, 1));
    av_image_fill_arrays(pFrameYUV->data, pFrameYUV->linesize,out_buffer,
        AV_PIX_FMT_YUV420P, pCodecCtx->width, pCodecCtx->height, 1);

    packet = (AVPacket *)av_malloc(sizeof(AVPacket));

    //Output Info-----------------------------
    printf("--------------- File Information ----------------\n");
    av_dump_format(pFormatCtx,0,filepath,0);
    printf("-------------------------------------------------\n");
    img_convert_ctx = sws_getContext(pCodecCtx->width, pCodecCtx->height, pCodecCtx->pix_fmt,
                                     pCodecCtx->width, pCodecCtx->height, AV_PIX_FMT_YUV420P,
                                     SWS_BICUBIC, NULL, NULL, NULL);

    //（1）初始化SDL
    if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER)) {
        printf( "Could not initialize SDL - %s\n", SDL_GetError());
        return -1;
    }

    screen_w = pCodecCtx->width;
    screen_h = pCodecCtx->height;
    //SDL 2.0 Support for multiple windows
    //（2）创建window
    screen = SDL_CreateWindow("Simplest ffmpeg player's Window",
                              SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                              screen_w, screen_h, SDL_WINDOW_OPENGL);

    if (!screen) {
        printf("SDL: could not create window - exiting:%s\n",SDL_GetError());
        return -1;
    }

    //（3）创建renderer
    sdlRenderer = SDL_CreateRenderer(screen, -1, 0);
    //IYUV: Y + U + V  (3 planes)
    //YV12: Y + V + U  (3 planes)
    sdlTexture = SDL_CreateTexture(sdlRenderer, SDL_PIXELFORMAT_IYUV, SDL_TEXTUREACCESS_STREAMING,
                                   pCodecCtx->width, pCodecCtx->height);

    sdlRect.x=0;
    sdlRect.y=0;
    sdlRect.w=screen_w;
    sdlRect.h=screen_h;

    //SDL End----------------------
    // 9.读取音频流、视频流、字幕流，得到AVPacket数据包(未解码)
    while (av_read_frame(pFormatCtx, packet) >= 0) {
        if (packet->stream_index == videoindex) {
            // 10.解码过程：输入AVPacket，输出AVFrame
            ret = avcodec_decode_video2(pCodecCtx, pFrame, &got_picture, packet);
            if(ret < 0){
                printf("Decode Error.\n");
                return -1;
            }
            if (got_picture) {
                sws_scale(img_convert_ctx, (const unsigned char* const*)pFrame->data, pFrame->linesize, 0, pCodecCtx->height,
                    pFrameYUV->data, pFrameYUV->linesize);

                //SDL---------------------------
#if 0
                SDL_UpdateTexture( sdlTexture, NULL, pFrameYUV->data[0], pFrameYUV->linesize[0] );
#else
                //（4）更新YUV
                SDL_UpdateYUVTexture(sdlTexture, &sdlRect,
                pFrameYUV->data[0], pFrameYUV->linesize[0],
                pFrameYUV->data[1], pFrameYUV->linesize[1],
                pFrameYUV->data[2], pFrameYUV->linesize[2]);
#endif

                SDL_RenderClear( sdlRenderer );
                // (5)复制到renderer
                SDL_RenderCopy( sdlRenderer, sdlTexture,  NULL, &sdlRect);
                // (6)
                SDL_RenderPresent( sdlRenderer );
                //SDL End-----------------------
                //Delay 40ms
                SDL_Delay(40);
            }
        }
    }
    //flush decoder
    //FIX: Flush Frames remained in Codec
    // darcy: 暂时没有理解此处的作用，删除后同样播放
    while (1) {
        ret = avcodec_decode_video2(pCodecCtx, pFrame, &got_picture, packet);
        if (ret < 0)
            break;
        if (!got_picture)
            break;
        sws_scale(img_convert_ctx, (const unsigned char* const*)pFrame->data, pFrame->linesize, 0, pCodecCtx->height,
            pFrameYUV->data, pFrameYUV->linesize);

        //SDL---------------------------
        SDL_UpdateTexture( sdlTexture, &sdlRect, pFrameYUV->data[0], pFrameYUV->linesize[0] );
        SDL_RenderClear( sdlRenderer );
        SDL_RenderCopy( sdlRenderer, sdlTexture,  NULL, &sdlRect);
        SDL_RenderPresent( sdlRenderer );
        //SDL End-----------------------
        //Delay 40ms
        SDL_Delay(40);
    }

    sws_freeContext(img_convert_ctx);
    SDL_Quit();
    av_frame_free(&pFrameYUV);
    av_frame_free(&pFrame);
    avcodec_close(pCodecCtx);
    avformat_close_input(&pFormatCtx);
    av_packet_free(&packet);

    return 0;
}