#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <syslog.h>
#include <errno.h>

extern int errno;

time_t tcpc(server) 
	struct sockaddr_in *server; /* server address                     */ 
{
	 int s;	
    unsigned long   time_to_set; 
	 char time_buffer[sizeof time_to_set];

	 printf("In TCP\n");

	 /*
     * Get a stream socket.
     */
    if ((s = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        syslog(LOG_WARNING, "socket: %s\n", strerror(errno));
		  perror("getservbyname");
        exit(__LINE__);
    }

    /*
     * Connect to the server.
     */
    if (connect(s, server, sizeof(*server)) < 0)
    {
        syslog(LOG_WARNING,
		  			"connect to %s:%d: %s\n",
					inet_ntoa(server->sin_addr),
					ntohs(server->sin_port),
		  			strerror(errno));
		  perror("connect");
		  abort();
        exit(__LINE__);
    }

    /*
     * The server sends the time w/o prompting
     */
    if (recv(s, time_buffer, sizeof(time_buffer), 0) < 0)
    {
        syslog(LOG_WARNING, "recv: %s\n", strerror(errno));
		  perror("recv");
		  abort();
        exit(__LINE__);
    }
	 time_to_set = (*(unsigned long *) time_buffer);
    printf("%d: At the beep ... %ld\n", __LINE__,  time_to_set);

    /*
     * Close the socket.
     */
    close(s);

  	 return  time_to_set;
}
