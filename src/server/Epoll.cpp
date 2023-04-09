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
#include"Epoll.h"

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
    
private:
    int epfd;
    struct epoll_event evs[MAX_EVENTS_NUM];

};


int Epoll::add(int fd,__uint32_t events){
    struct epoll_event epe;
    epe.data.fd = fd;
    epe.events = events;
    return epoll_ctl(epfd,EPOLL_CTL_ADD,fd,&epe);
}


int Epoll::wait(){
    int cnt = epoll_wait(epfd,evs,MAX_EVENTS_NUM,-1);/*block*/
    return cnt;
}

int Epoll::del(struct epoll_event epe){
    return epoll_ctl(epfd,EPOLL_CTL_DEL,epe.data.fd,&epe);
}