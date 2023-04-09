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

//webserver start


int ret;


int main(int argc,char *argv[]){
    
    //create socket_fd
    int sockfd = socket(AF_INET,SOCK_STREAM,0);
    if(sockfd == -1){
        std::cout<<"webserver start failed !"<<std::endl;
        return 1;
    }

    //set socket_fd unblock
    int flags = fcntl(sockfd,F_GETFL,0);
    fcntl(sockfd,F_SETFL,flags|O_NONBLOCK);

    //bind 
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


    //listen
    ret = listen(sockfd,MAX_LISTEN_NUM);
    if(ret<0){
        std::cout<<"webserver listen failed !"<<std::endl;
        return 1;
    }

    //create epoll_fd
    Epoll ep(1024);
    ep.add(sockfd,EPOLLIN);
    

    //
    while(1){
        int cnt = ep.wait();
        for(int i=0;i<cnt;i++){
            if()
        }
    }





    return 0;
}