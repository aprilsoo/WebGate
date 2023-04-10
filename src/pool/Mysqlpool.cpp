




#include"Mysqlpool.h"

MYSQL* Mysqlpool::ask(){
    std::unique_lock<std::mutex> unl(mutex);

    if((ed+1)%size == st) return NULL;
    ed = (ed+1)%size;
    return mysql[ed];
    
}