/*
 * Include Files.
 */

#include "config.h"
#include "rdate.h"

#include <ctype.h>

extern int errno;
extern int sys_nerr;
extern char *sys_errlist[];

unsigned long tcpc();
unsigned long udpc();

int
set_time(now)
	unsigned long now;
{
	char *		timestr;
	time_t		clock;
	struct tm 	*tmp;
	struct timeval tv;
	char			buffer[BUFSIZ];

	gettimeofday(&tv, NULL);
	clock = tv.tv_sec;
	tmp = gmtime(&clock);
	
	strftime(buffer, sizeof buffer, "%c", &tmp);
	printf("%d: clock %ld, previous time: %s\n", __LINE__, clock, buffer);


   printf("%d: At the beep ... %ld\n", __LINE__,  now);

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

extern int errno;

/*
 * Client Main.
 */
main(argc, argv)
int argc;
char **argv;
{
	unsigned short use_datagram = 1; /* Assume UDP by default   	*/
   unsigned short port;       /* port client will connect to       */
	char *argv0;
	time_t time;
	unsigned long   time_to_set;
	char time_buf[sizeof(time_to_set)];  /* data buffer for receive  */
	struct hostent *hostnm;    /* server host name information       */
	struct servent *serv_info; /* service number				     		  */
	struct sockaddr_in server; /* server address                     */
	int s;                     /* client socket                      */
	int rc;

	/* 
		Setting this in two steps avoid problems with large unsigned 
		constants using the ~1986 BSD ~1986 C compiler.
	 */
	unsigned long   internet_to_unix_delta = 22089888;
	internet_to_unix_delta *= 100;

	/* Store the name of the program */
	argv0 = strrchr(argv[0], '/');

	if ( argv0 != NULL)
		argv0++;
	else 
		argv0 = argv[0]; 

	openlog(argv0, LOG_PID | LOG_CONS, LOG_DAEMON);
	setlogmask(LOG_UPTO(LOG_INFO));

    /*
     * Check Arguments Passed. Should be hostname.  FIXME: (use getopt, add port)
     */
    if (argc < 2) {
        syslog(LOG_WARNING, "Usage: %s [-t] hostname\n", argv[0]);
        printf("Usage: %s -t] hostname\n", argv[0]);
        exit(__LINE__);
    }

	 if (!strcmp(argv[1], "-t")) {
	 	use_datagram = 0;
		printf("using TCP\n");
	 }
	 else
		printf("using UDP\n");

    /*
     * The server name is the last argument. Convertito server address.
     */
    hostnm = gethostbyname(argv[argc - 1]);
    if (hostnm == (struct hostent *) 0)
    {
        syslog(LOG_WARNING, "gethostbyname %s failed\n", argv[1]);
        perror("gethostbyname", argv[1]);
        exit(__LINE__);
    }

    /*
     * The port is hardcoded.  FIXME (see above)
     */
	serv_info = getservbyname("time", use_datagram ? "udp" : "tcp");
	if (serv_info == NULL) {
		syslog(LOG_WARNING,
			  "Getservbyname %s failed: %s\n",
			  "time", 
			  herror("time"));
	   perror("getservbyname", argv[1]);
		exit(__LINE__);
	}

    /*
     * Put the server information into the server structure.
     * The port must be put into network byte order.
     */
    server.sin_family      = AF_INET;
    server.sin_port        = serv_info->s_port;  /* Already in network byte order */
    server.sin_addr.s_addr = *((unsigned long *)hostnm->h_addr);

	 /* Get time in (network order) seconds via UDP or TCP */
	 /* time_to_set = use_datagram ? udpc(&server) : tcpc(&server); */
	 time_to_set = tcpc(&server);
   printf("%d: At the beep ... %ld\n", __LINE__,  time_to_set);

	/*
				Convert time from Internet (bigendian order)
				to local system order
	 */
	time_to_set = ntohl(*(unsigned long *) time_buf);
   printf("%d: At the beep ... %ld\n", __LINE__,  time_to_set);
	
	/*
				Now convert the target time from
				Internet (epoch 00:00:00 UTC on 1 January 1900)
				 to UNIX (epoch 00:00:00 UTC on 1 January 1970)
	*/
	time_to_set = time_to_set - internet_to_unix_delta;
   printf("%d: At the beep ... %ld\n", __LINE__,  time_to_set);

	rc = set_time(time_to_set);
	exit(rc ? 0 : 99);
}
