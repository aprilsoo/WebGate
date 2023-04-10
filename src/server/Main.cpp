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
#include"../pool/ThreadPoll.h"
#include"../http/Fsm.h"

//webserver start


int ret;


int main(){
    
    //创建socket套接字
    int sockfd = socket(AF_INET,SOCK_STREAM,0);
    if(sockfd == -1){
        std::cout<<"webserver start failed !"<<std::endl;
        return 1;
    }

    //设置非阻塞
    int flags = fcntl(sockfd,F_GETFL,0);
    fcntl(sockfd,F_SETFL,flags|O_NONBLOCK);

    //绑定
    struct sockaddr_in saddr;
    memset(&saddr,0,sizeof(saddr));

    saddr.sin_family = AF_INET;
    
    #ifndef IP_ADDR
        saddr.sin_addr.s_addr = htonl(INADDR_ANY);
    #else
        saddr.sin_addr.s_addr = inet_addr(IP_ADDR);
    #endif

    saddr.sin_port = htons(PORT);

    ret = bind(sockfd,(struct sockaddr*)&saddr,sizeof(saddr));
    if(ret<0){
        std::cout<<"webserver bind failed !"<<std::endl;
        return 1;
    }


    //监听
    ret = listen(sockfd,MAX_LISTEN_NUM);
    if(ret<0){
        std::cout<<"webserver listen failed !"<<std::endl;
        return 1;
    }

    //创建EPOLL
    Epoll ep(1024);
    ep.add(sockfd,EPOLLIN);
    
    //线程池
    ThreadPoll tp(20,1024);
    Task task;

    //epoll_wait，读取到任务时将任务加入任务队列，
    while(1){
        int cnt = ep.wait();
        for(int i=0;i<cnt;i++){
            if(ep.evs[i].data.fd == sockfd && (ep.evs[i].events & EPOLLIN)){
                struct sockaddr_in client_;
                socklen_t len = sizeof(client_);
                int client_fd = accept(sockfd,(sockaddr *)&client_,&len);
                ep.add(client_fd,EPOLLIN | EPOLLET);
            }else if(ep.evs[i].events & EPOLLIN){
                task.fd = ep.evs[i].data.fd;
                task.func = Fsm::test;
                while(tp.add_task(task)!=-1);
                
            }
        }
    }





    return 0;
}