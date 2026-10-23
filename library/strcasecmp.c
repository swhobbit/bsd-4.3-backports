/*------------------------------------------------------------------- */
/*                          STRCASECOMP C                             */
/*                                                                    */
/*         Compare two strings in a case insensitive fashion          */
/*                                                                    */
/*                Date: 19 Oct 2026                                   */
/*              Author: ahd@kew.com (Drew Derbyshire)                 */
/*             Address: Kendra Electronic Wonderworks                 */
/*                      Kenmore, WA                                   */
/*------------------------------------------------------------------- */

#include <sys/types.h>
#include <sys/param.h>
#include <ctype.h>

int strcasecmp(s1, s2)
	char *s1;
	char *s2;
{
	int i;
	int delta;
	size_t len = MIN(strlen(s1), strlen(s2));

	/* 
		We check one char past the length of the shorter string
		because if equal length both strings will terminate
		with the (equal) '\0', else one string will have an
		ASCII character higher and we'll return unequal.
	 */
		
	for (i = 0; i <= len; i++) {
		char c1 = s1[i];
		char c2 = s2[i];

		if (isupper(c1)) 
			c1 = tolower(c1);
		if (isupper(c2)) 
			c2 = tolower(c2);

		delta = c1 - c2;
		if (delta)
			return delta;
	}

	return 0;			/* Maxwell house: Equal to last drop. */
}
