/*------------------------------------------------------------------- */
/*                             HOST C                                 */
/*                                                                    */
/*            Perform basic look up of a Internet host by             */
/*            name or IP address                                      */
/*                                                                    */
/*                Date: 13 Oct 2026                                   */
/*              Author: ahd@kew.com (Drew Derbyshire)                 */
/*             Address: Kendra Electronic Wonderworks                 */
/*                      Kenmore, WA                                   */
/*------------------------------------------------------------------- */

#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <ctype.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>

/*------------------------------------------------------------------- */
/*         Do basic check that parameter is an IPv4 address           */
/*------------------------------------------------------------------- */

int
is_ipv4_addr(text)
	char * text;
{
	int column;

    for (column = 0; column < strlen(text); column++ ) {

         if (isdigit(text[column]))
         {
			continue;
         }

         if (text[column] == '.')
         {
			continue;
         }
	   	
         return 0;                /* Not IP address */
    }

    return 1;                     /* It IS an address */
}


/*------------------------------------------------------------------- */
/*   Main program to look up name/address provided on command line    */
/*------------------------------------------------------------------- */

int
main(argc, argv)
	int argc;
	char **argv;
{
	char    *argv0;	    /* program name */

    struct hostent *result = NULL;
    struct in_addr address;

    /* Store the name of the program */
    argv0 = strrchr(argv[0], '/');
    if (argv0)
		argv0++;
    else
		argv0 = argv[0];


#ifdef __DATE__
	printf("%s: Built %s %s\n",  argv0, __DATE__, __TIME__);
#endif

    if (argc == 1) {
         printf("%s: No arguments. Usage:\n\t%s hostname\n\t%s IP-address\n",
		argv0,
		argv0,
		argv0);
         exit(__LINE__);
    }

    if (is_ipv4_addr(argv[1])) {
         unsigned long address = inet_addr(argv[1]);
		 if (address == 0xffffffff) {
			printf("%s: String \"%s\" cannot be parsed as an IP address\n",
				   argv0,
				   argv[1]);
			exit(__LINE__);
		 }
         result = gethostbyaddr(&address, sizeof(address), AF_INET);
    }
    else {
         result = gethostbyname(argv[1]);
    }

    if (result == NULL) {
#ifdef __STDC__
		 herror(argv[1]);
#else
         printf("%s: look up failed: %s\n",
                argv0,
                get_herror(argv[1]));
#endif
         exit(__LINE__);
    }

    memset(&address, 0, sizeof address);
    memcpy((void *) &address, result->h_addr, sizeof address);

	if (is_ipv4_addr(argv[1])) {
		printf("%s has a domain name pointer to %s\n",
				argv[1],
				result->h_name); 
	} else {
		if (strcasecmp(argv[1], result->h_name)) {
			printf("%s is an alias for %s\n",
				   argv[1],
				   result->h_name);
		}
		memset(&address, 0, sizeof address);
		memcpy((void *) &address,
			   result->h_addr_list[0],
			   sizeof address);
		printf("%s has address %s\n",
				result->h_name,
				(char *) inet_ntoa(address));
	}

    if (result->h_aliases[0] != NULL) {
         size_t entry = 0;
         printf("Aliases:\n");

         while (result->h_aliases[entry] != NULL) {
              printf("\t%s\n", result->h_aliases[entry]);
              entry++;
         }
    }

    memset(&address, 0, sizeof address);

    if (result->h_addr_list[1] != NULL) {
         size_t entry = 0;
         printf("Addresses:\n");

         while (result->h_addr_list[entry] != NULL) {
            memcpy((void *) &address,
				   result->h_addr_list[entry],
				   sizeof address);
            printf("\t%s\n", (char *) inet_ntoa(address));
            entry++;
         }

    }

    exit(0);
}
