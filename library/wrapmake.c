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

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/dir.h>
#include <time.h>
#include <unistd.h>

#include <kewstr.h>

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
	program_name = (NULL == program_name) ? strdup(argv[0]) : strdup(program_name +1);

	if (argc > 1) {
		filename = argv[1];
	}
	else { 
		errno = E2BIG;
		fprintf(stderr, "%s: Missing required file name argument\n", program_name);
		exit(errno);
	}

	if (stat("NO_WRAPMAKE", buffer) == 0)
	{
		/* Just invoke the original make unaltered */
		printf("%s Invoking orginal makewfile unaltered.\n", program_name);
		execv("/bin/make", &argv[2]);
		perror("/bin/make");
	}

	now [strlen(now) -1] = '\0';
	printf("%s: Current time and date (%s)\n", program_name, now);

	/* Wed Oct 28 18:34:26 2026 */
	strtok(now, blank);					/* day name, ignored	*/
	mmm		= strtok(NULL, blank);		/* 3 letter month		*/
	day		= strtok(NULL, blank);		/* day of month 		*/ 
	hhmmss	= strtok(NULL, blank);		/* 24 hour time			*/
	year	= strtok(NULL, blank);		/* 4 digit year			*/

	child_argv[child_argc++] = "/bin/make";

    sprintf(buffer, "MAKE=%s %s", argv[0], filename);
    child_argv[child_argc++] = strdup(buffer);

	sprintf(buffer, "__DATE__=%s %s %s", mmm, day, year);
	child_argv[child_argc++] = strdup(buffer);

#ifdef DEBUG
	printf("INT  >>>\t%d\t%s\n", child_argc - 1, child_argv[child_argc - 1]);
#endif

	sprintf(buffer, "__TIME__=%s", hhmmss);
	child_argv[child_argc++] = strdup(buffer);

#ifdef DEBUG
	printf("INT  >>>\t%d\t%s\n", child_argc - 1, child_argv[child_argc - 1]);
#endif

#ifdef DEBUG
	printf("INT  >>>\t%d\t%s\n", child_argc - 1, child_argv[child_argc - 1]);
	printf("\nOpening file %s with %d byte buffer after %d generated arguments\n\n",
		   filename,
		   sizeof buffer,
		   child_argc - 1);
#endif

	
	stream = fopen(filename, "r");
	if (NULL == stream) {
		perror(filename);
		printf("%s: %s\n", program_name, strerror(filename));
		exit(errno);
	}

	line = buffer;				/* So it's not NULL */
	while (line != NULL) {
		
		line = fgets(buffer, sizeof buffer, stream);	
		if (NULL == line) {
#ifdef DEBUG
			printf("FILE >>>\t*** EOF ***\n");
#endif
			break;
		}

		ptr = strrchr(line, '\n');
		if (ptr != NULL) {
			*ptr = '\0';
		}

		if (strlen(line) == 1 &&  *line == '\n') {
			continue; 					/* Empty (before EOF)? Skip. */
		}

		child_argv[child_argc++] = strdup(line);
		if (NULL == child_argv[child_argc - 1] ) {
			perror(strdup);
			exit(errno);
		}

		if (strlen(child_argv[child_argc - 1]) != strlen(line)) {
			abort();
		}

#ifdef DEBUG
		printf("FILE >>>\t%d\t\"%s\"\t(%d bytes)\n",
				child_argc - 1,
				child_argv[child_argc - 1],
				strlen(line));
#endif
	}

#ifdef DEBUG
	printf("\nClosing file %s after %d arguments processed\n\n", filename, child_argc - 1);
#endif

	/* Add command line arguments */
	while(arg_used < argc) {
		child_argv[child_argc++] = argv[arg_used++];

#ifdef DEBUG
	printf("CLI  >>>\t%d\t%s\n", child_argc - 1, child_argv[child_argc - 1]);
#endif

	}
		
#ifdef DEBUG
	printf("\nDone after %d total arguments\n", child_argc - 1);
#endif

	child_argv[child_argc++] = (char *) NULL; /* Terminate arg list */
	
	fclose(stream);

	printf("%s: Generated %d arguments:\n\n", program_name, child_argc - 2);

	for (child_argc = 0; child_argv[child_argc] != NULL; child_argc++) {
		printf("%s ", child_argv[child_argc]);
	}

	putc('\n\n\n', stdout);
	fflush(stdout);

	execv(child_argv[0], child_argv);
	perror(child_argv[0]);

	return errno;
}
