#ifndef _WSA_TRACER_H
#define _WSA_TRACER_H

#include <iostream>
#include <ostream>

#include <stdarg.h>

static const int skdebug = 1;
#define MAX_ARGS 1024

#ifdef _WIN32
#if !defined(__PRETTY_FUNCTION__)
#define __PRETTY_FUNCTION__ __FUNCSIG__
#endif
#endif

namespace wsa{
    class Channel{
        friend class Trace;
        std::ostream* trace_file;

        public:
            Channel(std::ostream* o = &std::cout):trace_file(o){}
            void reset(std::ostream* o){trace_file = o;}


        void trace(const char* fn, const char* format, ...){
            char bf[MAX_ARGS] = {0};
            va_list arg;
            va_start(arg, format);
            vsnprintf(bf, MAX_ARGS, format, arg);
            va_end(arg);
            std::cout << "[" << fn << "]: " << bf << std::endl;
        }

        static Channel *Instance(){
            static Channel instance;
            return &instance;
        }
    };

    class Trace{
        public:
        Trace(const char *s, Channel* c){
            if(skdebug){
                name = s;
                cl = c;
                if(cl->trace_file)*cl->trace_file << name << " enter" << std::endl;
                //qDebug() << sshot::SystemUtil::getCPUTime() << ": "  << name << " enter";
            }
        }

        ~Trace()
        {
            if(skdebug){
                //qDebug() << sshot::SystemUtil::getCPUTime() << ": " << name << " exit";
                if(cl->trace_file){
                    *cl->trace_file << name << " exit" << std::endl;
                }
            }
        }

        private:
            const char *name;
            Channel    *cl;
    };
}

#define SK_TRACE_FUNC() wsa::Trace MY_TRACER(__PRETTY_FUNCTION__, wsa::Channel::Instance());
#define WSA_TRACE(...)    wsa::Channel::Instance()->trace(__PRETTY_FUNCTION__, __VA_ARGS__)
// #define WSA_DEBUG(...)    wsa::Channel::Instance()->debug(__VA_ARGS__)
// #define WSA_INFO(...)     wsa::Channel::Instance()->info(__VA_ARGS__)
// #define WSA_WARN(...)     wsa::Channel::Instance()->warn(__VA_ARGS__)
// #define WSA_ERROR(...)    wsa::Channel::Instance()->error(__VA_ARGS__)
// #define WSA_CRITICAL(...) wsa::Channel::Instance()->critical(__VA_ARGS__)

#endif //_WSA_TRACER_H