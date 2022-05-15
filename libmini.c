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

long sigaction(int signum, const struct sigaction *act, struct sigaction *oldact){
    struct k_sigaction new={}, old={};

    new.sa.sa_handler = act->sa_handler;
    new.sa.sa_flags = act->sa_flags | SA_RESTORER;
    new.sa.sa_restorer = sys_rt_sigreturn;
    new.sa.sa_mask = act->sa_mask;

    long ret = sys_rt_sigaction(signum, &new, &old, sizeof(long));

    oldact->sa_handler = old.sa.sa_handler;
    oldact->sa_flags = old.sa.sa_flags;
    oldact->sa_restorer = old.sa.sa_restorer;
    oldact->sa_mask = old.sa.sa_mask;

    WRAPPER_RETval(long);
}

int sigprocmask(int how, const sigset_t *set, sigset_t *oldset){
    int ret = sys_rt_sigprocmask(how, set, oldset, sizeof(long));
    WRAPPER_RETval(int);
}

int sigpending(sigset_t *set){
    int ret = sys_rt_sigpending(set, sizeof(long));
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

// signal
sighandler_t signal(int signum, sighandler_t handler){
    struct sigaction act={}, oldact={};

    act.sa_handler = handler;
    sigemptyset(&act.sa_mask);
    act.sa_flags = 0;

    int ret = sigaction(signum, &act, &oldact);
    
    if(ret==-1) return SIG_ERR;
    else return oldact.sa_handler;
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
    *set |=  1<<(signum-1);
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

#define	PERRMSG_MIN	0
#define	PERRMSG_MAX	34

static const char *errmsg[] = {
	"Success",
	"Operation not permitted",
	"No such file or directory",
	"No such process",
	"Interrupted system call",
	"I/O error",
	"No such device or address",
	"Argument list too long",
	"Exec format error",
	"Bad file number",
	"No child processes",
	"Try again",
	"Out of memory",
	"Permission denied",
	"Bad address",
	"Block device required",
	"Device or resource busy",
	"File exists",
	"Cross-device link",
	"No such device",
	"Not a directory",
	"Is a directory",
	"Invalid argument",
	"File table overflow",
	"Too many open files",
	"Not a typewriter",
	"Text file busy",
	"File too large",
	"No space left on device",
	"Illegal seek",
	"Read-only file system",
	"Too many links",
	"Broken pipe",
	"Math argument out of domain of func",
	"Math result not representable"
};

void perror(const char *prefix) {
	const char *unknown = "Unknown";
	long backup = errno;
	if(prefix) {
		write(2, prefix, strlen(prefix));
		write(2, ": ", 2);
	}
	if(errno < PERRMSG_MIN || errno > PERRMSG_MAX) write(2, unknown, strlen(unknown));
	else write(2, errmsg[backup], strlen(errmsg[backup]));
	write(2, "\n", 1);
	return;
}