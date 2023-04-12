#include<cstdio>
#include<iostream>
#include<fstream>
#include<sstream>
#include<string>
#include<unistd.h>
#include<errno.h>
#include<sys/epoll.h>

#include"Fsm.h"
#include"../tool/Logger.h"
#include"Httpparse.h"

Fsm* Fsm::fsm = new Fsm;


void Fsm::test(int fd,int epfd){
    Httpparse hp(fd);
    if(hp.status == -1){
        // debug("parse failed");
    }
    info("body_buffer:%s",hp.body_buffer);
    info("请求行:%d %d %s",hp.method,hp.version,hp.url);

}


void Fsm::response(int epfd,struct epoll_event ev){
    int fd = ev.data.fd;

    Httpparse hp(fd);
    if(hp.status == -1){
        epoll_ctl(epfd,EPOLL_CTL_DEL,fd,&ev);
        return;
    }
    
     
}