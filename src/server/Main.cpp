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
#include<netdb.h>
#include<netinet/in.h>

#include <arpa/inet.h>   

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

    #ifndef IP_ADDR
        saddr.sin_addr.s_addr = INADDR_ANY;
    #else
        int www = inet_pton(AF_INET,IP_ADDR,&saddr.sin_addr.s_addr);
        debug("www=%d",www);
    #endif

    saddr.sin_port = htons(PORT);
    saddr.sin_family = AF_INET;
    
    //设置端口复用
    int opt = 1;
	setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

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


    try{
        //创建EPOLL
        Epoll ep(1024);
        ep.add(sockfd,EPOLLIN);
        
        debug("epoll ok");
        
        //线程池
        ThreadPoll tp(20,1024);
 
        debug("thread ok");
        Task task;
        char hostname[128] = {0};
        char servername[128] = {0};
        while(1){
            int cnt = ep.wait();
            // debug("cnt = %d",cnt);
            for(int i=0;i<cnt;i++){
                if(ep.evs[i].data.fd == sockfd && (ep.evs[i].events & EPOLLIN)){
                    struct sockaddr_in client_;
                    socklen_t len = sizeof(client_);

                    int client_fd = accept(sockfd,(sockaddr *)&client_,&len);
                    ep.add(client_fd,EPOLLIN | EPOLLET);
                    
                    memset(hostname,0,sizeof(hostname));
                    memset(servername,0,sizeof(servername));
                    ret = getnameinfo((struct sockaddr *)&client_, sizeof(client_), 
                    hostname, sizeof(hostname), servername, sizeof(servername), 0);

                    info("新建连接: ip=%s port=%s fd=%d",hostname,servername,client_fd);
        
                    // info("连接 ip=%s  port=%s",inet_ntoa(client_),ntohs(client_.sin_port));
                }else if(ep.evs[i].events & EPOLLIN){
                    task.ev = ep.evs[i];
                    task.func = Fsm::response;
                    task.epfd = ep.get_epfd();
                    while(tp.add_task(task)!=-1);
                }
            }
        }

    }catch(...){
        std::cout<<"服务器坏喽"<<std::endl;
        fatal("服务器坏喽");
    }

    //epoll_wait，读取到任务时将任务加入任务队列，
    
    





    return 0;
}