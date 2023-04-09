#ifndef __EPOLL__
#define __EPOLL__

#include<iostream>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<cstring>
#include<cstdio>
#include<algorithm>
#include<sys/epoll.h>
#include<unistd.h>
#include<fcntl.h>


#include"../config.h"

class Epoll{
public:
    Epoll()=delete;
    Epoll(const Epoll &x)=delete;
    Epoll& operator = (const Epoll &x) = delete;
    ~Epoll(){
        close(epfd);
    }

    Epoll(int sz){
        epfd = epoll_create(sz);
    }
    int add(int fd,__uint32_t events);
    int del(struct epoll_event epe);
    int wait();



    
    struct epoll_event evs[MAX_EVENTS_NUM];

private:
    int epfd;
    
};



#endif