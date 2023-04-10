#include<cstdio>
#include<iostream>
#include<cstring>
#include<cstdarg>
#include<time.h>
#include<unistd.h>



#include"../config.h"
#include"Logger.h"

int Logger::cnt = 0;
int Logger::quick_push = 0;
char* Logger::logbuffer = nullptr;
std::fstream Logger::fd = std::fstream();
std::mutex Logger::mutex;
Logger* Logger::logger = new Logger();

void Logger::timer(){
    while(1){
        sleep(LOGGER_FLUSH_TIME);
        std::unique_lock<std::mutex> unl(mutex);
        log_file();
        unl.unlock();
    }
}

void Logger::log(int level,const char * file,const int line,const char *text,...){
    if(level < LOGGER_LIMIT) return;

    struct tm *local;
    time_t tim;
    tim = time(NULL);
    local = localtime(&tim);

    va_list va_ptr;
    va_start(va_ptr,text);
    int text_size = vsnprintf(NULL,0,text,va_ptr);
    va_end(va_ptr);


    std::unique_lock<std::mutex> unl(mutex);

    if(64 + text_size > LOGGER_BUFFER-cnt || quick_push == 1){
        log_file();
    }

    if(level == Logger::DEBUG)cnt += sprintf(logbuffer+cnt,"%s ","DEBUG");
    else if(level == Logger::INFO)cnt += sprintf(logbuffer+cnt,"%s ","INFO");
    else if(level == Logger::WARN)cnt += sprintf(logbuffer+cnt,"%s ","WARN");
    else if(level == Logger::ERROR)cnt += sprintf(logbuffer+cnt,"%s ","ERROR");
    else if(level == Logger::FATAL)cnt += sprintf(logbuffer+cnt,"%s ","FATAL");
    
    cnt += strftime(logbuffer+cnt,32,"%F %T ",local);
    cnt += sprintf(logbuffer+cnt,"%s:%d\n",file,line);

    va_start(va_ptr,text);
    cnt += vsprintf(logbuffer+cnt,text,va_ptr);
    va_end(va_ptr);

    cnt += sprintf(logbuffer+cnt,"\n");

    if(64 > LOGGER_BUFFER-cnt || quick_push == 1){
        log_file();
    }
}

void Logger::log_file(){
    if(!fd.is_open())return;
    fd.write(logbuffer,cnt);
    fd.flush();
    cnt=0;
    

    // fd.close();
    // fd.open(LOGGER_PATH);
}

