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



int Epoll::add(int fd,__uint32_t events){
    struct epoll_event epe;
    epe.data.fd = fd;
    epe.events = events;
    int w = epoll_ctl(epfd,EPOLL_CTL_ADD,fd,&epe);
    debug("sockfd in epoll is %d" ,w);
    return w;
}


int Epoll::wait(){
    int cnt = 0;
    try{
        cnt = epoll_wait(epfd,evs,MAX_EVENTS_NUM,-1);/*block*/
    }catch(...){
        perror("");
    }

    return cnt;
}

int Epoll::del(struct epoll_event epe){
    return epoll_ctl(epfd,EPOLL_CTL_DEL,epe.data.fd,&epe);
}
