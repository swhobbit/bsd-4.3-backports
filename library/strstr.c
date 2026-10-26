/*------------------------------------------------------------------- */
/*                            strstr.c                                */
/*                                                                    */
/*                      find a string in another string.              */
/*                                                                    */
/*                Date: 20 Sep 2024                                   */
/*              Author: ahd@kew.com (Drew Derbyshire)                 */
/*             Address: Kendra Electronic Wonderworks                 */
/*                      Kenmore, WA                                   */
/*------------------------------------------------------------------- */

#include <stdio.h>
#include <string.h>

char * 
strstr(haystack, needle) 
	char *haystack, *needle;
{
	int hl = strlen(haystack);
	int nl = strlen(needle);
	int i;

	for (i = 0; i < (hl-nl+1); i++) {
		if (!strncmp(haystack + i, needle, nl)) {	
			return haystack + i;	/* Found the needle */
		}
	}

	return NULL;		/* Needle not found */
}
