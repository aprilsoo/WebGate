#include<cstdio>
#include<iostream>
#include<fstream>
#include<sstream>
#include<string>
#include<unistd.h>

#include"Fsm.h"
#include"../tool/Logger.h"


Fsm* Fsm::fsm = new Fsm;




void Fsm::test(int fd){
    char str[4096];
    int cnt = 0;

    while(1){
        int len = read(fd,str+cnt,sizeof(str));
        if(len <= 0){
            if(errno == EINTR || errno == EAGAIN)break;
            return;
        }else{
            cnt+=len;
        }
    }

    info(str);

}