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

typedef sigset_t kernel_sigset_t;

typedef int mode_t;
typedef int uid_t;
typedef int gid_t;
typedef int pid_t;

typedef void (*sighandler_t)(int);
typedef void (*__sighandler_t)(int);
typedef void (*__sigrestore_t)(void);

struct timespec {
    time_t tv_sec;        /* seconds */
    long   tv_nsec;       /* nanoseconds */
};

struct sigaction {
    __sighandler_t sa_handler;
    unsigned int sa_flags;
    __sigrestore_t sa_restorer;
    sigset_t sa_mask;
};

struct k_sigaction {
    struct sigaction sa;
};

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

#define	SIG_ERR	 ((sighandler_t) -1)	/* Error return.  */
#define	SIG_DFL	 ((sighandler_t)  0)	/* Default action.  */
#define	SIG_IGN	 ((sighandler_t)  1)	/* Ignore signal.  */

#define SA_NOCLDSTOP	0x00000001u
#define SA_NOCLDWAIT	0x00000002u
#define SA_SIGINFO	    0x00000004u
#define SA_ONSTACK  	0x08000000u
#define SA_RESTART	    0x10000000u
#define SA_INTERRUPT    0x20000000u
#define SA_NODEFER	    0x40000000u
#define SA_RESETHAND	0x80000000u

#define SA_NOMASK	SA_NODEFER
#define SA_ONESHOT	SA_RESETHAND

#define SA_RESTORER	0x04000000

// ------- functions -------
// syscall fuinction
unsigned int sys_alarm(unsigned int);
void sys_exit(int);
int sys_nanosleep(const struct timespec *, struct timespec *);
int sys_pause(void);
int sys_rt_sigaction(int, const struct k_sigaction *, struct k_sigaction *, size_t);
int sys_rt_sigprocmask(int, const kernel_sigset_t *, kernel_sigset_t *, size_t);
int sys_rt_sigpending(kernel_sigset_t *, size_t);
void sys_rt_sigreturn();
unsigned int sys_sleep(unsigned int);
ssize_t sys_write(int fd, const void *, size_t);

// syscall wrapper function
unsigned int alarm(unsigned int seconds);
void exit(int status);
int nanosleep(const struct timespec *req, struct timespec *rem);
int pause(void);
long sigaction(int signum, const struct sigaction *act, struct sigaction *oldact);
int sigprocmask(int how, const sigset_t *set, sigset_t *oldset);
int sigpending(sigset_t *set);
unsigned int sleep(unsigned int seconds);
ssize_t write(int fd, const void *buf, size_t count);

// signal
sighandler_t signal(int signum, sighandler_t handler);

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