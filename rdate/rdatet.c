/*
 * Include Files.
 */

#include "config.h"
#include "rdate.h"

#include <ctype.h>

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


int
set_time(now)
	unsigned long now;
{
	char *		timestr;
	time_t		clock;
	struct tm 	*tmp;
	struct timeval tv;

	tv.tv_sec = now;
	tv.tv_usec = 0;

	if (settimeofday(&tv, NULL)) {
		syslog(LOG_WARNING,
			   "could not set system time: %s",
			   strerror(errno));
		
		return 1;
	} else {

		clock = gettimeofday(&tv, NULL);

		tmp = gmtime(&clock);
		timestr = asctime(tmp);
		timestr[strlen(timestr) - 1] = 0;

		syslog(LOG_NOTICE, "System clock set to %s\n", timestr);

		clock = time(0);
		tmp = localtime(&clock);
		timestr = asctime(tmp);
		timestr[strlen(timestr) - 1] = 0;

		syslog(LOG_NOTICE, "Local clock set to %s\n", timestr);

		return 0;
	}
}

/*
 * Client Main.
 */
main(argc, argv)
int argc;
char **argv;
{
    unsigned short port;       /* port client will connect to       */
	char *argv0;
	time_t time;
	unsigned long   time_to_set;
    char time_buf[sizeof(time)];  /* data buffer for send/receive    */
    struct hostent *hostnm;    /* server host name information       */
	struct servent *serv_info; /* service number				     */
    struct sockaddr_in server; /* server address                     */
    int s;                     /* client socket                      */

	unsigned long   net_to_unix_delta = 22089888;

	net_to_unix_delta *= 100;

	/* Store the name of the program */
	argv0 = strrchr(argv[0], '/');

	if ( argv0 != NULL)
		argv0++;
	else 
		argv0 = argv[0]; 

	openlog(argv0, LOG_PID | LOG_CONS, LOG_DAEMON);
	setlogmask(LOG_UPTO(LOG_INFO));

    /*
     * Check Arguments Passed. Should be hostname and port.
     */
    if (argc != 3)
    {
        syslog(LOG_WARNING, "Usage: %s hostname port\n", argv[0]);
        exit(1);
    }

    /*
     * The host name is the first argument. Get the server address.
     */
    hostnm = gethostbyname(argv[1]);
    if (hostnm == (struct hostent *) 0)
    {
        syslog(LOG_WARNING, "gethostbyname %s failed\n", argv[1]);
        exit(2);
    }


    /*
     * The port is the second argument.
     */
	 if (isdigit(argv[2][1])) {
		port = (unsigned short) atoi(argv[2]);
	 } else {
		serv_info = getservbyname(argv[2], "tcp");

		if (serv_info == NULL) {
		   syslog(LOG_WARNING,
				  "Getservbyname %s failed: %s\n",
				  argv[2], 
				  strerror("time"));
		   exit(5);
		}
		port = htons(serv_info->s_port);
	 }

    /*
     * Put the server information into the server structure.
     * The port must be put into network byte order.
     */
    server.sin_family      = AF_INET;
    server.sin_port        = htons(port);
    server.sin_addr.s_addr = *((unsigned long *)hostnm->h_addr);

    /*
     * Get a stream socket.
     */
    if ((s = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        syslog(LOG_WARNING, "socket: %s\n", strerror(errno));
        exit(3);
    }

    /*
     * Connect to the server.
     */
    if (connect(s, &server, sizeof(server)) < 0)
    {
        syslog(LOG_WARNING, "connect %s\n", strerror(errno));
        exit(4);
    }

    /*
     * The server sends the time w/o prompting
     */
    if (recv(s, time_buf, sizeof(time_buf), 0) < 0)
    {
        syslog(LOG_WARNING, "recv: %s\n", strerror(errno));
        exit(6);
    }

    /*
     * Close the socket.
     */
    close(s);

	/* See inetd's builtins.c for an explanation */
	time_to_set = ntohl(*(unsigned long *) time_buf);
	time_to_set = time_to_set - net_to_unix_delta;

	exit(set_time(time_to_set) ? 0 : 99);
}
