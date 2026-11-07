/*------------------------------------------------------------------- */
/*                           WRAPMAKE C                               */ 
/*                                                                    */
/*          Generate ANSI STD __DATE_ and __TIME__ constants          */
/*          as an include file for a pre-ANSI C (Jurassic)            */
/*          environment.                                              */
/*                                                                    */
/*                Date: 28 Oct 2026                                   */
/*              Author: ahd@kew.com (Drew Derbyshire)                 */
/*             Address: Kendra Electronic Wonderworks                 */
/*                      Kenmore, WA                                   */
/*------------------------------------------------------------------- */

#include <kewstr.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <errno.h>
#include <sys/dir.h>

extern int errno;

int main(argc, argv) 
	int argc;
	char **argv;
{

	char *program_name;
	int arg_used = 0;
	char *filename = argv[arg_used++];
	
	FILE *stream;

	char * day;
	char * mmm;
	char * hhmmss;
	char * year;
	char * blank = " ";
	char * line;
	char * ptr;
	char buffer[BUFSIZ];
	char quote = '"';

	char *child_argv[50];
	int  child_argc = 0;

	long clock = time(0); 
	char * now = ctime(&clock); 

	/*
		Report only program base name in messages, leaving
		original full name intact.
	 */
	program_name = strrchr(argv[0] , '/');
	program_name = (program_name == NULL) ? strdup(argv[0]) : strdup(program_name +1);

	if (argc > 1) {
		filename = argv[1];
	}
	else { 
		errno = E2BIG;
		fprintf(stderr, "%s: Missing file name argument\n", program_name);
		exit(errno);
	}

	now [strlen(now) -1] = '\0';
	printf("%s: Current time and date (%s)\n", program_name, now);

	/* Wed Oct 28 18:34:26 2026 */
	strtok(now, blank);				/* day name, ignored	*/
	mmm		= strtok(NULL, blank);		/* 3 letter month		*/
	day		= strtok(NULL, blank);		/* day of month 		*/ 
	hhmmss	= strtok(NULL, blank);		/* 24 hour time			*/
	year	= strtok(NULL, blank);		/* 4 digit year			*/

	child_argv[child_argc++] = "/bin/make";

	sprintf(buffer, "__DATE__=%c%s %s %s%c", quote,  mmm, day, year, quote);
	child_argv[child_argc++] = strdup(buffer);

	sprintf(buffer, "__TIME__=%c%s%c", quote, hhmmss, quote);
	child_argv[child_argc++] = strdup(buffer);

    sprintf(buffer, "MAKE=%c%s %s%c", quote, argv[0], filename, quote);
    child_argv[child_argc++] = strdup(buffer);

	stream = fopen(filename, "r");
	if (stream == NULL) {
		perror(filename);
		printf("%s: %s\n", program_name, strerror(filename));
		exit(errno);
	}

	while (line != NULL) {
		
		line = fgets(buffer, sizeof buffer, stream);	
		if (line == NULL) {
			printf("EOF\n");
			break;
		}
		else {
			line = strdup(line);	

			if (line = NULL) {
				perror(strdup);
				exit(errno);
			}

			ptr = strrchr('\n');
			if (ptr != NULL) {
				*ptr = '\0';
			}

			/* DEBUG */
			child_argv[child_argc++] = strdup(line);
			printf(">>>\t%d\t%s\n", child_argc - 1, child_argv[child_argc -1]);
		}
	}

	/* Add command line arguments */
	while(arg_used < argc) {
		child_argv[child_argc++] = argv[arg_used++];
	}

	child_argv[child_argc++] = (char *) NULL; /* Terminate arg list */
	
	fclose(stream);

	printf("%s: Generated %d arguments: ", program_name, child_argc - 1);

	for (child_argc = 0; child_argv[child_argc] != NULL; child_argc++) {
		printf("%s ", child_argv[child_argc]);
	}

	putc('\n', stdout);

	execv(child_argv[0], child_argv);
	perror(child_argv[0]);

	return errno;
}
