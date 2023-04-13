#include<cstdio>
#include<unistd.h>
#include<thread>
#include <condition_variable>
#include<iostream>
#include<memory>


#include"ThreadPoll.h"


int ThreadPoll::add_task(Task task){
    if((ed+1)%size_task == st) return -1;
    
    tasks[ed].ev = task.ev;
    tasks[ed].epfd = task.epfd;
    tasks[ed].func = task.func;

    ed = (ed+1)%size_task;
    cv.notify_one();

    return 0;
}

void run(ThreadPoll *tp){
    Task now_task;
    while(1){
        {
            std::unique_lock<std::mutex> unl(tp->task_mutex);
            while(tp->st == tp->ed){
                tp->cv.wait(unl);
            }
            now_task = tp->tasks[tp->st];
            tp->st = (tp->st+1)%tp->size_task;
        }
        now_task.func(now_task.epfd , now_task.ev);
    }
}