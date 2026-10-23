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
