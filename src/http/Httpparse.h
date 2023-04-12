#ifndef _HTTPPARSE_
#define _HTTPPARSE_

#include<sys/types.h>

#define MAX_READ_BUFFER 4096

#include "../tool/Logger.h"

enum Method{
    GET=0,
    POST,
    HEAD,
    PUT,
    DELETE,
    CONNECT,
    OPTIONS,
    TRACE,
    PATCH
};

enum Version{
    HTTP1_0 =0,
    HTTP1_1
};

struct Headers{
    
};

class Httpparse{
public:
    int fd;
    int method;
    int version;
    int status;

    char *url;
    
    int header_num;
    char **header_buffer;
    char *body_buffer;

    

    Httpparse(int _fd);
    ~Httpparse();
};

#endif