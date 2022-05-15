#ifndef __LIBMINI_H__
#define __LIBMINI_H__

// --------- type ----------
typedef long long size_t;
typedef long long ssize_t;
typedef long long off_t;
typedef long long time_t;

typedef int mode_t;
typedef int uid_t;
typedef int gid_t;
typedef int pid_t;

struct timespec {
    time_t tv_sec;        /* seconds */
    long   tv_nsec;       /* nanoseconds */
};

// -------- symbol ---------
#define NULL ((void*)0)
extern long errno;

// ------- constant --------


// ------- functions -------
// syscall fuinction
unsigned int sys_alarm(unsigned int);
void sys_exit(int);
int sys_nanosleep(const struct timespec *, struct timespec *);
int sys_pause(void);
unsigned int sys_sleep(unsigned int);
ssize_t sys_write(int fd, const void *, size_t);

// syscall wraper function
unsigned int alarm(unsigned int seconds);
void exit(int status);
int nanosleep(const struct timespec *req, struct timespec *rem);
int pause(void);
unsigned int sleep(unsigned int seconds);
ssize_t write(int fd, const void *buf, size_t count);

// string function
size_t strlen(const char *s);

#endif