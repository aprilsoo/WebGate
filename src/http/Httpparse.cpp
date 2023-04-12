
#include<iostream>
#include<cstring>
#include<cstdio>
#include<unistd.h>



#include"Httpparse.h"

Httpparse::Httpparse(int _fd){
    fd = _fd;
    status = -1;

    char buf[MAX_READ_BUFFER];
    int ret = read(fd,buf,MAX_READ_BUFFER);
    if(ret <= 0){
        
        return;
    }
    
    
    char met[16]="";
    char tmp[256]="";
    char ver[16]="";
    
    sscanf(buf,"%16[^ ] %256[^ ] %16[^\r\n]\r\n",met,tmp,ver);
    info("%s",buf);

    if(strcasecmp(met,"GET")==0)method = GET;
    else if(strcasecmp(met,"POST")==0)method = POST;
    else if(strcasecmp(met,"HEAD")==0)method = HEAD;
    else if(strcasecmp(met,"PUT")==0)method = PUT;
    else if(strcasecmp(met,"DELETE")==0)method = DELETE;
    else if(strcasecmp(met,"CONNECT")==0)method = CONNECT;
    else if(strcasecmp(met,"OPTIONS")==0)method = OPTIONS;
    else if(strcasecmp(met,"TRACE")==0)method = TRACE;
    else if(strcasecmp(met,"PATCH")==0)method = PATCH;
    else return;


    if(strcasecmp(ver,"HTTP/1.0")==0)version = HTTP1_0;
    else if(strcasecmp(ver,"HTTP/1.1")==0)version = HTTP1_1;
    else return ;


    url = (char*)malloc(strlen(tmp));
    if(url == NULL){
        return;
    }

    memcpy(url,tmp,strlen(tmp));

    int len = strlen(met)+strlen(tmp)+strlen(ver) + 4;
    int buf_len = strlen(buf);

    header_num = 0;
    char *rec_header[256];

    while(1){
        int w = sscanf(buf+len,"%[^\r\n]\r\n",tmp);
        if(w > 0){
            len +=strlen(tmp) + 2;
            if(len>buf_len)return;
            //解析头部消息
            
            rec_header[header_num] = (char*)malloc(strlen(tmp));
            memcpy(rec_header[header_num],tmp,strlen(tmp));
            header_num++;
            // info("headers : %s",tmp);
        }else if(w == 0){
            len+=2;
            break;
        }
    }
    
    header_buffer = (char **)malloc(sizeof(char*)*header_num);

    for(int i=0;i<header_num;i++){
        header_buffer[i] = rec_header[i];
    }

    body_buffer = (char*)malloc(buf_len - len);
    memcpy(body_buffer,buf+len,buf_len-len);

    status = 0;
}

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

Httpparse::~Httpparse(){
    
    try{
        free(body_buffer);
        free(url);
        for(int i=0;i<header_num;i++){
            free(*header_buffer);
        }
        free(header_buffer);
        
    }catch(...){

    }
    
}