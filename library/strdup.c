/*------------------------------------------------------------------- */
/*                            STRDUP C                                */
/*                                                                    */
/*            Duplicate a string into malloc()'d memory               */
/*                                                                    */
/*                Date: 30 Oct 2026                                   */
/*              Author: ahd@kew.com (Drew Derbyshire)                 */
/*             Address: Kendra Electronic Wonderworks                 */
/*                      Kenmore, WA                                   */
/*------------------------------------------------------------------- */

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

char *strdup(from)
	char *from;
{
	char *to;

	if (NULL == from) {
		return NULL;
	}

	to = malloc(strlen(from) + 1);

	if (NULL == to) {
		/* Error code already set */
		return NULL;
	}

	return strcpy(to, from);

}
