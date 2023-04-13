
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
    info("%s %s %s",met,tmp,ver);
    // info("%s",buf);

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



Httpparse::~Httpparse(){
    
    try{
        // free(body_buffer);
        // free(url);
        // for(int i=0;i<header_num;i++){
        //     free(header_buffer[i]);
        // }
        // free(header_buffer);
        
    }catch(...){

    }
    
}