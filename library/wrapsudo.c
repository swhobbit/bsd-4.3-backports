/*------------------------------------------------------------------- */
/*                           WRAPSUDO C                               */
/*                                                                    */
/*            Simple wrapper for BSD 4.3 UNIX program "sudo" which    */
/*            doesn't natively support the "-s" flag to fire off      */
/*            an interactive shell as root. (It doesn't support a     */
/*            lot of things that modern sudo does, but that's the     */
/*            most popular option.)                                   */
/*                                                                    */
/*                Date: 23 Nov 2026                                   */
/*              Author: ahd@kew.com (Drew Derbyshire)                 */
/*             Address: Kendra Electronic Wonderworks                 */
/*                      Kenmore, WA                                   */
/*------------------------------------------------------------------- */

#include <errno.h>
#include <memory.h>
#include <stdio.h>
#include <stdlib.h>

#include <kewstr.h>

int
main(argc, argv)
	int argc;
	char *argv[];
{
	char **parameters;
	char *shell = getenv("SHELL");
	int rc;

	if (NULL == shell) {
		/* This being for BSD 4.3, we assume user loves csh if not set */
		shell = "/bin/sh";
	}

	switch(argc)
	{
		case 1:
			/* No user argments, a user error */
			fprintf(stderr,
					  "usage: %s -s\nusage: %s command\n",
					  argv[0],
					  argv[0]);
			exit(EINVAL);
			break;
			 
		case 2:
			/* 
				One CLI parameter specified, it's either:
				-  The "-s" flag to fire up a shell or
				-  Something else, like a one word command (or a bad option flag).
			 */
			if (!strcmp(argv[1], "-s")) {
				rc = execlp("sudo", "sudo", shell, NULL);
				break;						/* Done processing, head for the exit */
			}
			/* FALL THROUGH to general case to handle it, whatever it is */

		default:
			/* General case we'll just send to sudo to handle */
			parameters = (char **) malloc((argc + 1) * sizeof argv[0]);
			memcpy(parameters, argv, argc * sizeof argv[0]);
			parameters[0] = "sudo";
			parameters[argc + 1] = NULL;
			
			rc = execvp(parameters[0], parameters);
			break;
		
	}

	/* If we get here, then the exec call failed. We report the error and exit. */

	perror(argv[0]);
	exit(errno);
}
