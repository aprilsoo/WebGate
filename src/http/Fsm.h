#ifndef _FSM_
#define _FSM_

enum Response{
    Res_OK=200,
    Res_NOT_FOUND=404
};

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
