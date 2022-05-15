#ifndef __LIBMINI_H__
#define __LIBMINI_H__

// --------- type ----------
typedef long long size_t;
typedef long long ssize_t;
typedef long long off_t;

typedef int mode_t;
typedef int uid_t;
typedef int gid_t;
typedef int pid_t;

// -------- symbol ---------
extern long errno;

#define NULL ((void*)0)

// ------- constant --------


// ------- functions -------

// syscall function
void exit(int status);
ssize_t write(int fd, const void *buf, size_t count);

// string function
size_t strlen(const char *s);

#endif