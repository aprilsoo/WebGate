#ifndef _FSM_
#define _FSM_

class Fsm{
public:

    static void test(int fd,int epfd);
    static void response(int epfd,struct epoll_event ev);


private:

    
    static Fsm *fsm;

    Fsm(){}
    ~Fsm(){}

};



#endif
