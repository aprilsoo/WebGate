#include<cstdio>
#include<iostream>
#include<fstream>
#include<sstream>
#include<string>
#include<unistd.h>
#include<errno.h>
#include<sys/epoll.h>
#include<fstream>
#include <sys/stat.h>
#include <fcntl.h>
#include<sys/stat.h>
#include<time.h>



#include"Fsm.h"
#include"../tool/Logger.h"
#include"Httpparse.h"

Fsm* Fsm::fsm = new Fsm;

char *get_mime(char* name){
    char* dot;
    dot = strrchr(name, '.');
    if (dot == (char*)0)
        return "text/plain; charset=utf-8";
    if (strcmp(dot, ".html") == 0 || strcmp(dot, ".htm") == 0)
        return "text/html; charset=utf-8";
    if (strcmp(dot, ".jpg") == 0 || strcmp(dot, ".jpeg") == 0)
        return "image/jpeg";
    if (strcmp(dot, ".gif") == 0)
        return "image/gif";
    if (strcmp(dot, ".png") == 0)
        return "image/png";
    if (strcmp(dot, ".css") == 0)
        return "text/css";
    if (strcmp(dot, ".au") == 0)
        return "audio/basic";
    if (strcmp( dot, ".wav") == 0)
        return "audio/wav";
    if (strcmp(dot, ".avi") == 0)
        return "video/x-msvideo";
    if (strcmp(dot, ".mov") == 0 || strcmp(dot, ".qt") == 0)
        return "video/quicktime";
    if (strcmp(dot, ".mpeg") == 0 || strcmp(dot, ".mpe") == 0)
        return "video/mpeg";
    if (strcmp(dot, ".vrml") == 0 || strcmp(dot, ".wrl") == 0)
        return "model/vrml";
    if (strcmp(dot, ".midi") == 0 || strcmp(dot, ".mid") == 0)
        return "audio/midi";
    if (strcmp(dot, ".mp3") == 0)
        return "audio/mpeg";
    if (strcmp(dot, ".ogg") == 0)
        return "application/ogg";
    if (strcmp(dot, ".pac") == 0)
        return "application/x-ns-proxy-autoconfig";

    return "text/plain; charset=utf-8";
}

void Fsm::test(int fd,int epfd){
    Httpparse hp(fd);
    if(hp.status == -1){
        // debug("parse failed");
    }
    info("body_buffer:%s",hp.body_buffer);
    info("请求行:%d %d %s",hp.method,hp.version,hp.url);

}

int send_file(int fd ,const char *pwd){
    struct stat buf_stat;
    int ret = stat(pwd,&buf_stat);
    if(ret != 0)return -1;


    int fd_file = open(pwd,O_RDONLY);
    if(fd_file == -1)return -1;

    char txt[buf_stat.st_size]="";
    
    int len = read(fd_file,txt,sizeof(txt));
    if(len == -1) return -1;

    write(fd,txt,sizeof(txt));

    return 0;
}

int send_response_head(int fd,int ver,int res){
    char txt[16]="";

    if(ver == HTTP1_0) strcat(txt,"HTTP/1.0");
    else if(ver == HTTP1_1) strcat(txt,"HTTP/1.1");
    else return -1;

    if(res == Res_OK) strcat(txt," 200 OK\r\n");
    else if(res == Res_NOT_FOUND) strcat(txt," 404 	Not Found\r\n");
    else return -1;

    write(fd,txt,strlen(txt));

}

int send_headers(int fd,char *pwd){
    char buf[256] = "";

    char *type_file = get_mime(pwd);
    strcat(buf,"Content-Type:");
    strcat(buf,type_file);
    strcat(buf,"; charset=utf-8\r\n");

    
    strcat(buf,"\r\n");
    write(fd,buf,strlen(buf));
}

void Fsm::response(int epfd,struct epoll_event ev){
    int fd = ev.data.fd;

    Httpparse hp(fd);
    if(hp.status == -1){
        epoll_ctl(epfd,EPOLL_CTL_DEL,fd,&ev);
        return;
    }

    debug("parse ok ");
    
    char pwd_path[256]="";
	char * path = getenv("PWD");
    strcat(pwd_path,path);
    strcat(pwd_path,"/../Website");

    if(strcmp(hp.url,"/")==0){
        hp.url = "/main.html";
    }

    strcat(pwd_path,hp.url);

    int ret;

    ret = access(pwd_path,F_OK);
    if(ret == -1){
        memset(pwd_path,0,sizeof(pwd_path));
        strcat(pwd_path,path);
        strcat(pwd_path,"/../Website/404.html");
    }

    info("%s",pwd_path);
    
    send_response_head(fd,hp.version,Res_OK);
    send_headers(fd,pwd_path);
    send_file(fd,pwd_path);
    
	// chdir(pwd_path);
    epoll_ctl(epfd,EPOLL_CTL_DEL,fd,&ev);
}