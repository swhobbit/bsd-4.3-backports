/*------------------------------------------------------------------- */
/*                             HOST C                                 */
/*                                                                    */
/*     Perform basic look up a Inter host by name or IP address       */
/*                                                                    */
/*                Date: 13 Oct 2026                                   */
/*              Author: ahd@kew.com (Drew Derbyshire)                 */
/*             Address: Kendra Electronic Wonderworks                 */
/*                      Kenmore, WA                                   */
/*------------------------------------------------------------------- */

#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/socket.h>

extern char *get_herror();

#include "get_herror.c"


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
    struct hostent *result = NULL;

#ifdef __DATE__
	printf("%s %s %s\n",  argv[0], __DATE__, __TIME__);
#endif

    if (argc == 1) {
         printf("%s Missing arguments\n", argv[0]);
         exit(__LINE__);
    }

    if (is_ipv4_addr(argv[1])) {
         unsigned long address = inet_addr(argv[1]);
		 if (address == 0xffffffff) {
			printf("%s: Address \"%s\" cannot be parsed.\n",
				   argv[0], argv[1]);
			exit(__LINE__);
		 }
         result = gethostbyaddr(&address, sizeof(address), AF_INET);
    }
    else {
		 printf("looking up name \"%s\"\n", argv[1]);
         result = gethostbyname(argv[1]);
    }

    if (result == NULL) {
         fprintf(stderr, "%s: look up of %s failed: %s\n",
                         argv[0],
                         argv[1],
                         get_herror());
         exit(__LINE__);
    }

    printf("%s resolves to canonical name %s (%s).\n",
           argv[1],
           result->h_name,
		   (char *) result->h_addr);

    if (result->h_aliases[0] != NULL) {
         size_t entry = 0;
         printf("Aliases:\n");

         while (result->h_aliases[entry] != NULL) {
              printf("\t%s\n", result->h_aliases[entry]);
              entry++;
         }
    }


    if (result->h_addr_list[1] != NULL) {
         size_t entry = 0;
         printf("Addresses:\n");

         while (result->h_addr_list[entry] != NULL) {
              printf("\t%s\n", (char *) result->h_addr_list[entry]);
              entry++;
         }

    }

    exit(0);
}
