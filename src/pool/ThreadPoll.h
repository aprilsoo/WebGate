#ifndef _THREADPOLL_
#define _THREADPOLL_

#include<queue>
#include<iostream>
#include<cstdio>
#include<thread>
#include<mutex>
#include <condition_variable>

#include"Mysqlpool.h"
#include"../tool/Logger.h"
#include"../http/Fsm.h"


class ThreadPoll;

void run(ThreadPoll* tp);

struct Task{
    void (*func)(int fd);
    int fd;
};

class ThreadPoll{
public:
    ThreadPoll(unsigned int size_thread,unsigned int size_tsk){        
        size_thr = size_thread;
        size_task = size_tsk;
        size_free = size_thr;
        st=0,ed=0;

        debug("线程池申请%d %d",size_thread,size_tsk);
        
        try{
            tasks = (Task*)malloc(sizeof(Task)*size_task);
            if(tasks == NULL){
                throw "任务列表申请内存失败";
            }
            std::memset(tasks,0,sizeof(tasks));

            sqlpool = new Mysqlpool(size_thr);/*mysql连接池*/

            for(int i=0;i<1;i++){
                std::thread p1(run,this);
                p1.detach();
            }

            debug("线程成功创建");
        }catch(...){
            debug("线程池申请%d %d 失败",size_thread,size_tsk);
            throw ;
        }
        debug("线程池申请%d %d 成功",size_thread,size_tsk);
    }

    ~ThreadPoll(){
        free(tasks);
        
        delete sqlpool;
    }

    int add_task(Task task);
    
    unsigned int size_thr ;
    unsigned int size_task;
    unsigned int size_free;
    int st,ed;

    Task *tasks;
    Mysqlpool *sqlpool;
    std::mutex task_mutex;
    std::condition_variable cv;
private:
    

    
};



#endif