#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdio.h>

time_t udpc(server)
	 struct sockaddr_in *server; /* server afamily, address & port */
{

   int s;
   unsigned short port;
   struct sockaddr_in server;
   char time_buffer[4];
   unsigned long time_to_set;
   int nr;
   int fd;


	printf("In UDP\n");

   /* Create a datagram socket in the internet domain and use the
    * default protocol (UDP).
    */
   if ((s = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
   {
       perror("socket");
       exit(__LINE__);
   }

   /* Send the message in buf to the server */
   if (sendto(s, time_buffer, 0, 0, server, sizeof(server)) < 0)
   {
	   perror("sendto");
	   exit(__LINE__);
   }

   memset(time_buffer, 0, sizeof time_buffer);
   nr = recv(s, time_buffer, sizeof(time_buffer), 0);
   if (nr == -1) {
      perror("recv");
		exit(__LINE__);
   }

   /* Deallocate the socket */
   close(s);

	/* This value is Internet (Bigendian) order with Epoch 1900 */
   time_to_set = (*(unsigned long *) time_buffer);

   return time_to_set;
}
