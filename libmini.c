#include "libmini.h"

# define WRAPPER_RETval(type) errno = 0; if(ret<0){errno = -ret; return -1;} return ((type)ret);
# define WRAPPER_RETptr(type) errno = 0; if(ret<0){errno = -ret; return NULL;} return ((type)ret);

// declar variable
long errno;

// syscall wrapper
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

int sigprocmask(int how, const sigset_t *set, sigset_t *oldset){
    int ret = sys_rt_sigprocmask(how, set, oldset, sizeof(kernel_sigset_t));
    WRAPPER_RETval(int);
}

int sigpending(sigset_t *set){
    int ret = sys_rt_sigpending(set, sizeof(kernel_sigset_t));
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

// handle signal set 
int sigemptyset(sigset_t *set){
   *set = 0;
   return 0;
}

int sigfillset(sigset_t *set){
   *set = ~0;
   return 0;
}

int sigaddset(sigset_t *set, int signum){
   *set |= 1<<(signum-1);
   return 0;
}

int sigdelset(sigset_t *set, int signum){
   *set &= ~(1<<(signum-1));
   return 0;
}

int sigismember(const sigset_t *set, int signum){
   int ismem = *set & (1<<(signum-1));
   if(ismem != 0) return 1;
   return 0;
}

// string
size_t strlen(const char *s){
    size_t i=0;
    while (s[i]!='\0')++i;
    return i;
}

// print error
void perror(const char *prefix) {
    if(prefix) {
        write(2, prefix, strlen(prefix));
        write(2, ": error", 2);
    }
    return;
}
