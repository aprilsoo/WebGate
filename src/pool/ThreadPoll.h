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
        try{
            tasks = (Task*)malloc(sizeof(Task)*size_task);
            if(tasks == NULL){
                throw "申请内存失败";
            }
            std::memset(tasks,0,sizeof(tasks));

            sqlpool = new Mysqlpool(size_thr);

            threads = (std::thread *)malloc(sizeof(std::thread)*size_thr);

            for(int i=0;i<size_thr;i++){
                std::thread p1(run,*this);
                swap(threads[i],p1);
                threads[i].detach();
                p1.detach();
            }

        }catch(...){
            throw ;
        }
    }

    ~ThreadPoll(){
        free(tasks);
        free(threads);
        delete sqlpool;
    }

    int add_task(Task task);
    
    unsigned int size_thr ;
    unsigned int size_task;
    unsigned int size_free;
    int st,ed;

    Task *tasks;
    Mysqlpool *sqlpool;
    std::thread *threads;
    std::mutex task_mutex;
    std::condition_variable cv;
private:
    

    
};



#endif