#ifndef __EPOLL__
#define __EPOLL__

#include<iostream>
#include<cstring>
#include<cstdio>


#include"../config.h"
#include"../tool/Logger.h"


class Epoll{
public:
    Epoll()=delete;
    Epoll(const Epoll &x)=delete;
    Epoll& operator = (const Epoll &x) = delete;
    
    Epoll(int sz){
        epfd = epoll_create(sz);
        if(epfd == -1 ){
            throw "epfd failed";
        }

        debug("epfd = %d",epfd);
        evs = (struct epoll_event*)malloc(sizeof(struct epoll_event)*MAX_EVENTS_NUM);
        if(evs == NULL){
            throw "evs create failed";
            debug("evs malloc");
        }

        debug("epoll 创建成功");
    }

    ~Epoll(){
        close(epfd);
        free(evs);
    }

    
    int add(int fd,__uint32_t events);
    int del(struct epoll_event epe);
    int wait();

    struct epoll_event *evs;

private:
    int epfd;
};



#endif