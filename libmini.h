#ifndef __LIBMINI_H__
#define __LIBMINI_H__

// -------- symbol ---------
#define NULL ((void*)0)
extern long errno;
#define _SIGSET_NWORDS (1024 / (8 * sizeof (unsigned long int)))

// --------- type ----------
typedef long long size_t;
typedef long long ssize_t;
typedef long long off_t;
typedef long long time_t;
typedef long long clock_t;
typedef long long sigval_t;

typedef long sigset_t;

typedef int mode_t;
typedef int uid_t;
typedef int gid_t;
typedef int pid_t;

struct timespec {
    time_t tv_sec;        /* seconds */
    long   tv_nsec;       /* nanoseconds */
};

typedef sigset_t kernel_sigset_t;

// ------- constant --------
#define SIGHUP      1
#define SIGINT      2
#define SIGQUIT     3
#define SIGILL      4
#define SIGTRAP     5
#define SIGABRT     6
#define SIGIOT      6
#define SIGBUS      7
#define SIGFPE      8
#define SIGKILL     9
#define SIGUSR1     10
#define SIGSEGV     11
#define SIGUSR2     12
#define SIGPIPE     13
#define SIGALRM     14
#define SIGTERM     15
#define SIGSTKFLT   16
#define SIGCHLD     17
#define SIGCONT     18
#define SIGSTOP     19
#define SIGTSTP     20
#define SIGTTIN     21
#define SIGTTOU     22
#define SIGURG      23
#define SIGXCPU     24
#define SIGXFSZ     25
#define SIGVTALRM   26
#define SIGPROF     27
#define SIGWINCH    28
#define SIGIO       29
#define SIGPWR      30
#define SIGSYS      31

#define SIG_BLOCK   0
#define SIG_UNBLOCK 1
#define SIG_SETMASK 2

#define SIG_ERR     -1
#define SIG_DFL      0
#define SIG_IGN      1

// ------- functions -------
// syscall fuinction
unsigned int sys_alarm(unsigned int);
void sys_exit(int);
int sys_nanosleep(const struct timespec *, struct timespec *);
int sys_pause(void);
int sys_rt_sigprocmask(int, const kernel_sigset_t *, kernel_sigset_t *, size_t);
int sys_rt_sigpending(kernel_sigset_t *, size_t);
unsigned int sys_sleep(unsigned int);
ssize_t sys_write(int fd, const void *, size_t);

// syscall wrapper function
unsigned int alarm(unsigned int seconds);
void exit(int status);
int nanosleep(const struct timespec *req, struct timespec *rem);
int pause(void);
int sigprocmask(int how, const sigset_t *set, sigset_t *oldset);
int sigpending(sigset_t *set);
unsigned int sleep(unsigned int seconds);
ssize_t write(int fd, const void *buf, size_t count);

// signal set handler
int sigemptyset(sigset_t *set);
int sigfillset(sigset_t *set);
int sigaddset(sigset_t *set, int signum);
int sigdelset(sigset_t *set, int signum);
int sigismember(const sigset_t *set, int signum);

// string function
size_t strlen(const char *s);

// print error
void perror(const char *prefix);

#endif