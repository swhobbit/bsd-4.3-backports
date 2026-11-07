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

	if (from == NULL) {
		return NULL;
	}

	to = malloc(strlen(from) + 1);

	if (to == NULL) {
		/* Error code already set */
		return NULL;
	}

	return strcpy(to, from);

}
