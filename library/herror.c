/* vi: tabstop=4 sw=4 */

/*
 * 2026-10-02 Backported to BSD 4.3 by Drew Derbyshire (ahd@kew.com) at
 * Kendra Electronic Wonderworks, Kenmore WA.
 */


#include <netdb.h>
#include <stdio.h>
#include <string.h>

extern int      h_errno;	/* For TCP/IP library errors */

/* report text of h_errno */
char *
get_herror(prefix)
	char *prefix;
{

	static char     print_buffer[1024];

	sprintf(print_buffer, "%s: Network error %d: ", prefix, h_errno);

	switch (h_errno) {

        case HOST_NOT_FOUND:
            strcat(print_buffer, "Authoritative Answer Host not found");
            break;

        case TRY_AGAIN:
            strcat(print_buffer,
                    "Non-Authoritative Host not found, or SERVERFAIL");
            break;

        case NO_RECOVERY:
            strcat(print_buffer,
                    "Non recoverable errors: FORMERR, REFUSED, NOTIMP");
            break;

        case NO_ADDRESS:
            strcat(print_buffer,
                    "Valid host name, no address, look for MX record");
            break;

        default:
            sprintf(print_buffer + strlen(print_buffer),
                    "Unknown network error %d", h_errno);
            break;
    }

	return print_buffer;
}

#ifndef __STDC__

void
herror(prefix)
	char *prefix;
{
    printf(stderr, "%s", get_herror(prefix));
}    

#endif
