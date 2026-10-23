#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdio.h>

main(argc, argv)
int argc;
char **argv;
{


   int s;
   unsigned short port;
   struct sockaddr_in server;
   char time_buffer[4];
   unsigned long retval;
   int nr;
   int fd;
   unsigned long	net_to_unix_delta = 22089888;
   net_to_unix_delta *= 100;


   /* argv[1] is internet address of server argv[2] is port of server.
    * Convert the port from ascii to integer and then from host byte
    * order to network byte order.
    */
   if(argc != 3)
   {
      printf("Usage: %s <host address> <port> \n",argv[0]);
      exit(1);
   }
   port = htons(atoi(argv[2]));


   /* Create a datagram socket in the internet domain and use the
    * default protocol (UDP).
    */
   if ((s = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
   {
       perror("socket()");
       exit(1);
   }


   /* Set up the server name */
   server.sin_family      = AF_INET;            /* Internet Domain    */
   server.sin_port        = port;               /* Server Port        */
   server.sin_addr.s_addr = inet_addr(argv[1]); /* Server's Address   */

   /* Send the message in buf to the server */
   if (sendto(s, time_buffer, 0, 0, &server, sizeof(server)) < 0)
   {
	   perror("sendto()");
	   exit(__LINE__);
   }

   memset(time_buffer, 0, sizeof time_buffer);
   nr = recv(s, time_buffer, sizeof(time_buffer), 0);
   if (nr == -1) {
       perror("recv()");
	exit(__LINE__);
   }

   /* Deallocate the socket */
   close(s);

   retval = (*(unsigned long *) time_buffer);
   retval = ntohl(retval);
   printf("INET Seconds: %#lx\n", retval);
   printf("INET Seconds: %lu\n", retval);

   fputc('\n', stdout);

   retval -= net_to_unix_delta;
   printf("UNIX Seconds: %#lx\n", retval);
   printf("UNIX Seconds: %lu\n", retval);

   exit(0);
}
