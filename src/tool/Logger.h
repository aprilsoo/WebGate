#ifndef _LOGGER_
#define _LOGGER_

#include<cstdio>
#include<iostream>
#include<queue>
#include<memory>
#include <mutex>
#include<fstream>
#include<thread>
#include<cstring>


#include"./config.h"

/**
 * 日志系统
 * 日志级别 debug < info < warn < error < fatal
 * 
 */

#define debug(text,...) Logger::log(Logger::DEBUG,__FILE__,__LINE__,text,##__VA_ARGS__)
#define info(text,...) Logger::log(Logger::INFO,__FILE__,__LINE__,text,##__VA_ARGS__)
#define warn(text,...) Logger::log(Logger::WARN,__FILE__,__LINE__,text,##__VA_ARGS__)
#define error(text,...) Logger::log(Logger::ERROR,__FILE__,__LINE__,text,##__VA_ARGS__)
#define fatal(text,...) Logger::log(Logger::FATAL,__FILE__,__LINE__,text,##__VA_ARGS__)



class Logger{
public:
    enum LEVEL{
        DEBUG=0,
        INFO,
        WARN,
        ERROR,
        FATAL,
        LEVEL_SIZE
    };

    static void log(int level,const char * file,const int line,const char *text,...);
    static void log_file();
    static void timer();

    Logger * got(){
        return logger;
    }


private:
    static char *logbuffer;
    static int cnt;
    static int quick_push;
    static std::mutex mutex;
    
    static std::fstream fd;

    static Logger* logger;
    Logger(){
        fd.open(LOGGER_PATH,std::ios::app);
        logbuffer = (char*)malloc(sizeof(char)*LOGGER_BUFFER);
        std::memset(logbuffer,0,LOGGER_BUFFER);

        if(!fd.is_open()){
            std::cout<<"日志系统打开失败!"<<std::endl;
            return;
        }
        
        std::thread p1(timer);
        p1.detach();
        debug("日志打开");
    }

    ~Logger(){
        fd.close();
        free(logbuffer);
    }

};



#endif