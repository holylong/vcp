#include <stdio.h>

// ffmpeg
#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>
#include <libswscale/swscale.h>

void SaveFrame(AVFrame* pFrame, int width, int height, int iFrame){
    FILE *pFile;
    char szFileName[32];
    int y;

    // open file
    sprintf(szFileName, "frame%d.ppm", iFrame);
    pFile=fopen(szFileName, "wb");
    if(pFile == NULL)return;

    // Write header
    fprintf(pFile, "P6\n%d %d\n255\n", width, height);
    // Write pixel data
    for(y=0; y<height; y++){
        fwrite(pFrame->data[0] + y*pFrame->linesize[0], 1, width*3, pFile);
    }

    // Close file
    fclose(pFile);
}

int help(char* argv[]){
    fprintf(stderr, "please input arguments like: %s moive.mp4", argv[1]);

    return -1;
}

int main(int argc, char* argv[])
{
    if(argc < 2){
        return help(argv);
    }

    // initialize the library
    av_register_all();

    // open file
    AVFormatContext *pFormatCtx = NULL;
    if(avformat_open_input(&pFormatCtx, argv[1], NULL, NULL) != 0)return -1;

    // retrieve stream information
    if(avformat_find_stream_info(pFormatCtx, NULL) < 0)return -1;

    //dump information about file onto standart error
    av_dump_format(pFormatCtx, 0, argv[1], 0);

    int i;
    AVCodecContext *pCodecCtxOrig = NULL;
    AVCodecContext *pCodecCtx = NULL;

    // find first stream
    int videoStream = -1;
    int audioStream = -1;

    for(i = 0; i < pFormatCtx->nb_streams; i++){
        if(pFormatCtx->streams[i]->codec->codec_type == AVMEDIA_TYPE_VIDEO){
            videoStream = i;break;
        }

        if(pFormatCtx->streams[i]->codec->codec_type == AVMEDIA_TYPE_AUDIO){
            videoStream = i;break;
        }
    }

    if(videoStream == -1)return -1;

    // Get a pointer to the codec context for the video stream
    pCodecCtxOrig = pFormatCtx->streams[videoStream]->codec;

    AVCodec *pCodec = NULL;
    // Find the decoder for the  video stream
    pCodec = avcodec_find_decoder(pCodecCtxOrig->codec_id);
    if(pCodec==NULL){
        fprintf(stderr, "Unsupported codec!\n");return -1;
    }

    // Copy context
    pCodecCtx = avcodec_alloc_context3(pCodec);
    if(avcodec_copy_context(pCodecCtx, pCodecCtxOrig) != 0){
        fprintf(stderr, "Couldn't copy codec context");
        return -1;
    }

    // open codec
    if(avcodec_open2(pCodecCtx, pCodec, NULL)<0)return -1;

    // Allocate video frame;
    AVFrame *pFrame = NULL,*pFrameRGB = NULL;
    pFrame=av_frame_alloc();

    // Allocate an AVFrame structure
    pFrameRGB = av_frame_alloc();
    if(pFrameRGB == NULL){return -1;}

    uint8_t *buffer = NULL;
    int numBytes;

    //Determine required buffer size and allocate buffer
    numBytes = avpicture_get_size(AV_PIX_FMT_RGB24, pCodecCtx->width, pCodecCtx->height);
    buffer=(uint8_t*)av_malloc(numBytes*sizeof(uint8_t));

    // 将缓冲区的适当部分分配给 pFrameRGB 中的图像平面，pFrameRGB 是一个 AVFrame，但 AVFrame 是一个超集的AVPicture
    avpicture_fill((AVPicture*)pFrameRGB, buffer, AV_PIX_FMT_RGB24, pCodecCtx->width, pCodecCtx->height);

    // read data
    AVPacket packet;
    int frameFinished;
    struct SwsContext *sws_ctx = NULL;

    // init sws context for software scaling
    sws_ctx = sws_getContext(pCodecCtx->width, pCodecCtx->height, pCodecCtx->pix_fmt,
                            pCodecCtx->width, pCodecCtx->height, AV_PIX_FMT_RGB24,
                            SWS_BILINEAR, NULL, NULL, NULL);

    i = 0;
    while(av_read_frame(pFormatCtx, &packet) >= 0){
        // Is this a packet from the video stream?
        if(packet.stream_index == videoStream){
            // decode video frame
            avcodec_decode_video2(pCodecCtx, pFrame, &frameFinished, &packet);

            // did we get a video frame
            if(frameFinished){
                // Convert the image from its native format to RGB
                sws_scale(sws_ctx, (uint8_t const * const *) pFrame->data,
                         pFrame->linesize, 0, pCodecCtx->height, pFrameRGB->data, pFrameRGB->linesize);

                // save the frame to disk
                if(++i<=5){
                    SaveFrame(pFrameRGB, pCodecCtx->width, pCodecCtx->height, i);
                }
            }
        }
    }

    // free the packet that was allocated by av_read_frame
    av_free_packet(&packet);


    // free rgb buffer
    av_free(buffer);
    av_free(pFrameRGB);

    // free the yuv frame
    av_free(pFrame);

    // close the codecs
    avcodec_close(pCodecCtx);
    avcodec_close(pCodecCtxOrig);

    // close the video file
    avformat_close_input(&pFormatCtx);

    return 0;
}