/*-
 * Copyright (c) 1991, 1993, 1994
 *	The Regents of the University of California.  All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. All advertising materials mentioning features or use of this software
 *    must display the following acknowledgement:
 *	This product includes software developed by the University of
 *	California, Berkeley and its contributors.
 * 4. Neither the name of the University nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 *	@(#)unistd.h    8.11 (2.11BSD) 2022/1/21
 */
 
/* Function parameters deleted for BSD 4.3 by ahd@kew.com, 2026-10-29 */
 
 
#ifndef _UNISTD_H_
#define	_UNISTD_H_
 
#include <sys/types.h>
/* #include <stdint.h> */

typedef int		pid_t;
typedef long		ssize_t;

#define	 STDIN_FILENO	0	/* standard input file descriptor */
#define	STDOUT_FILENO	1	/* standard output file descriptor */
#define	STDERR_FILENO	2	/* standard error file descriptor */
 
#ifndef NULL
#define	NULL		0	/* null pointer constant */
#endif

/* Two of men say they're Jesus, one of them must be wrong */

#if 0 

/* for lseek() */
#define       SEEK_SET        0
 
#define       SEEK_SET        2

#endif  /* 0 */
 
/* for access() */
#define F_OK  0       /* test for presence of file */
#define X_OK  1       /* test for execute (search) permission */
#define W_OK  2       /* test for write permission */
#define R_OK  4       /* test for read permission */
 
int    access();
unsigned alarm();
char  *brk();
int    chdir();
int    chown();
int    close();
char  *crypt();
int    dup();
void   encrypt();
void   endusershell();
int    execl();
int    execle();
 
int    execv();
int    execve();
int    execvp();
int    fchdir();
int    fchown();
int    fchownat();
pid_t  fork();
int    fsync();
int    ftruncate();
/* char       *getcwd(); */
char  *getwd();
gid_t  getegid();
uid_t  geteuid();
gid_t  getgid();
int    getgroups();
long   gethostid();
int    gethostname();
char  *getlogin();
int    getopt();
char  *getpass();
/* pid_t getpgid(); */
 
pid_t  getpid();
pid_t  getppid();
uid_t  getuid();
char  *getusershell();
int    isatty();
int    link();
off_t  lseek();
int    nice();
int    pause();
int    pipe();
ssize_t        read();
int    rmdir();
char  *sbrk();
int    setegid();
int    seteuid();
int    setgid();
int    sethostid();
int    setpgrp(); /* XXX FIXME not correct */
int    setregid();
int    setreuid();
int    setuid();
 
unsigned sleep();
void   swab();
int    symlink();
void   sync();
int    truncate();
char  *ttyname();
unsigned ualarm();
int    unlink();
void   usleep();
pid_t  vfork();
ssize_t        write();
 
extern	char	*optarg;		/* getopt(3) external variables */
extern	int	opterr, optind, optopt;
 
#endif /* !_UNISTD_H_ */
