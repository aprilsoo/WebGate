#ifndef _MYSQLPOOL_
#define _MYSQLPOOL_


#include<mysql/mysql.h>
#include<cstdio>
#include<iostream>
#include<unistd.h>

#include"config.h"
#include"../tool/Logger.h"

class Mysqlpool{
public:
    Mysqlpool(unsigned int sz){
        size = sz;
        st=0,ed=0;
        debug("数据库连接池申请:%d",size);
        for(int i=0;i<size;i++){
            mysql[i] = new MYSQL;
            mysql_init(mysql[i]);
            MYSQL *ret = mysql_real_connect(mysql[i],MYSQL_HOST,MYSQL_USER,MYSQL_PWD,MYSQL_DATABASE,3306+i,NULL,0);
            if(ret == NULL){
                throw "数据库连接失败！";
            }
        }
    }

    MYSQL* ask();

    ~Mysqlpool(){
        for(int i=0;i<size;i++){
            mysql_close(mysql[i]);
        }
        debug("数据库连接池销毁:%d",size);
    }

    unsigned int size;
    int st,ed;
    MYSQL *mysql[MAX_POOL_SIZE];
    std::mutex mutex;

private:
    
};

#endif