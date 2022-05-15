#include "libmini.h"

# define WRAPPER_RETval(type) errno = 0; if(ret<0){errno = -ret; return -1;} return ((type)ret);
# define WRAPPER_RETptr(type) errno = 0; if(ret<0){errno = -ret; return NULL;} return ((type)ret);

// declar variable
long errno;

// syscall
unsigned int alarm(unsigned int seconds){
    return sys_alarm(seconds);
}

void exit(int status){
    sys_exit(status);
}

int nanosleep(const struct timespec *req, struct timespec *rem){
    int ret = sys_nanosleep(req, rem);
    WRAPPER_RETval(int);
}

int pause(void){
    int ret = sys_pause();
    WRAPPER_RETval(int);
}

unsigned int sleep(unsigned int seconds){
    struct timespec req = {seconds, 0};
    struct timespec rem = {0, 0};
    int ret = nanosleep(&req, &rem);
    if(ret==-1)return rem.tv_sec;
    else return 0;
}

ssize_t write(int fd, const void *buf, size_t count){
    long ret = sys_write(fd, buf, count);
    WRAPPER_RETval(ssize_t);
}

// string
size_t strlen(const char *s){
    size_t i=0;
    while (s[i]!='\0')++i;
    return i;
}
