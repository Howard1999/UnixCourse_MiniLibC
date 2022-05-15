#include "libmini.h"

# define WRAPPER_RETval(type) errno = 0; if(ret<0){errno = -ret; return -1;} return ((type)ret);
# define WRAPPER_RETptr(type) errno = 0; if(ret<0){errno = -ret; return NULL;} return ((type)ret);

long errno;

// syscall
ssize_t write(int fd, const void *buf, size_t count){
    long ret = sys_write(fd, buf, count);
    WRAPPER_RETval(ssize_t);
}

void exit(int status){
    sys_exit(status);
}

// string
size_t strlen(const char *s){
    size_t i=0;
    while (s[i]!='\0')++i;
    return i;
}
