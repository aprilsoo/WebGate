#include<cstdio>
#include<iostream>
#include<fstream>
#include<sstream>
#include<string>
#include<unistd.h>
#include<errno.h>


#include"Fsm.h"
#include"../tool/Logger.h"


Fsm* Fsm::fsm = new Fsm;




void Fsm::test(int fd){
    debug("fsm 执行 %d",fd);
    char str[4096];
    int cnt = 0;

    
    int len = read(fd,str+cnt,4096-cnt);
        
    if(len <= 0){
        if(errno == EINTR || errno == EAGAIN)return;
        return;
    }else{
        cnt+=len;
    }
    

    info("str = %s",str);

}