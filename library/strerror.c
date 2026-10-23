
/*
 * 2026-10-02 Backported to BSD 4.3 by Drew Derbyshire (ahd@kew.com) at
 * Kendra Electronic Wonderworks, Kenmore WA.
 */


extern int errno;
extern int sys_nerr;
extern char *sys_errlist[];

char * strerror(my_errno)
    int my_errno;
{
    static char s[1024];
    if (sys_nerr >= my_errno) {
      	return sys_errlist[my_errno];
    }
    else {
      	fprintf(stderr,
      		"*** Undocumented error %d (of %d): %s\n",
      		my_errno,
      		sys_nerr,
      		sys_errlist[my_errno]);
      	fflush(stderr);
      	return s;
    }
}

