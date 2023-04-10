

template<class T>
class ThreadPoll{
public:
    ThreadPoll(unsigned int size_thread,unsigned int size_task){
        size_thr = size_thread;
        vec_task.reserve(size_task);
    }


private:
    unsigned int size_thr ;
    queue<T> vec_task;
    
};