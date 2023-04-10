#include<cstdio>
#include<unistd.h>
#include<thread>
#include <condition_variable>
#include<iostream>



#include"ThreadPoll.h"


int ThreadPoll::add_task(Task task){
    if((ed+1)%size_task == st) return -1;
    ed = (ed+1)%size_task;
    tasks[ed] = task;
    cv.notify_one();

    debug("添加任务成功");
    return 0;
}

void run(ThreadPoll *tp){
    while(1){
        std::unique_lock<std::mutex> unl(tp->task_mutex);
        while(tp->st != tp->ed){
            tp->cv.wait(unl);
        }
        
        Task *now_task = new Task((tp->tasks[tp->st]));

        tp->st = (tp->st+1)%tp->size_task;

        unl.unlock();
        
        now_task->func(now_task->fd);
    }
}