/* vim: set tabstop=3 shiftwidth=3 noexpandtab:
 */

/*------------------------------------------------------------------- */
/*                           STRFTIME C                               */
/*                                                                    */
/*        BSD 4.3 compatible version of the function to return        */
/*         formatted time string based on provided template.          */
/*                                                                    */
/*                Date: 11 Nov 2026                                   */
/*              Author: ahd@kew.com (Drew Derbyshire)                 */
/*             Address: Kendra Electronic Wonderworks                 */
/*                      Kenmore, WA                                   */
/*------------------------------------------------------------------- */

#include <sys/time.h>
#include <sys/types.h>

#include <errno.h>
#include <memory.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

char  *timezone();
extern int errno;

size_t
strftime(result, result_size, format, input_tm)
	char   *result;
	size_t result_size;
	char *format;
	struct tm *input_tm;
{

	static char *month[] = {
		"January",
		"February",
		"March",
		"April",
		"May",
		"June",
		"July",
		"August",
		"September",
		"October",
		"November",
		"December"
	};
	
	static char *weekday[] = {
		"Sunday",
		"Monday",
		"Tuesday",
		"Wednesday",
		"Thursday",
		"Friday",
		"Caturday"
	};

	struct tm user_tm;			/* caller  date/time split into fields	*/
	struct tm now_tm;				/* current date/time split into fields */
	struct timeval tv;
	struct timezone tz;

	char buffer[BUFSIZ];

	size_t format_size = strlen(format);
	size_t column = 0;
	size_t used = 0;
	unsigned short is_unique_time;			/* Does current time match user time? */
	unsigned short is_gmt;						/* User requested GMT time zone */ 

	memset(result, '\0', result_size);
	memcpy(&user_tm, input_tm, (size_t) sizeof user_tm);	/* Prevent clobbering */

	if (gettimeofday(&tv, &tz) != 0) {
		/* Does anyone know what time it is? */
		perror("gettimeofday");
		abort();
	}

	/* Guess user time is in GMT; we'll set is_gmt next line. */
	memcpy(&now_tm, gmtime(&tv.tv_sec), (size_t) sizeof now_tm);

	is_gmt = now_tm.tm_hour == user_tm.tm_hour; 

	if (! is_gmt) {
		/* Not GMT time, make local time. */
		memcpy(&now_tm, localtime(&tv.tv_sec), (size_t) sizeof now_tm);
	}

	is_unique_time = memcmp(&now_tm, &user_tm, sizeof now_tm) ? 1 : 0;

	while ((used < result_size) && (column <= format_size)) {
		if ('%' == format[column++]) {

			switch(format[column++]) {

						/* PRE-FORMATTED DATE AND TIME STRINGS */

				/*
						Note: all result strings built from the
						compound date & time strings are short
						enough compared to our buffer we don't need
						check the nested strftime() calls for
						overflow.
				 */

				case 'c':
					/* ddd mmm dd hh:mm:ss zzz xm YYYY (BSD style) */
					strftime(buffer,
								(size_t) sizeof buffer,
						/* 	"%a %b %e %H:%M:%S %Y",  			*/	/* POSIX		*/
						/*	 	"%a %b %d %I:%M:%S %p %Z %Y",		*/	/* Linux 	*/
								"%a %b %d %I:%M:%S %Z %Y",			/* BSD 4.3	*/
								&user_tm);
					break;

				case '+':
					/* ddd mmm dd hh:mm:ss zzz xm YYYY (linux style) */
					strftime(buffer,
								(size_t) sizeof buffer,
							 	"%a %b %e %H:%M:%S %Y",  				/* POSIX		*/
								&user_tm);
					break;

				case 'D':
					/* USA date format, abhorred elsewhere */
					/* FALL THROUGH */
				case 'x':
					/* 'x' is Locale dependent, we assume USA: mm/dd/yy */
					strftime(buffer,
								(size_t) sizeof buffer,
								"%m/%d/%y",
								&user_tm);
					break;

				case 'F':
					/* ISO date: YYYY-MM-DD */
					strftime(buffer,
								(size_t) sizeof buffer,
								"%Y-%m-%d",
								&user_tm);
					break;

				case 'X':
					/* 'X' is locale dependent time, we assume USA: hh:mm:ss */
				case 'T':
					/* 'T' is time in ISO 8601 format hh:mm:ss */
					strftime(buffer,
								(size_t) sizeof buffer,
								"%H:%M:%S",
								&user_tm);
					break;

				case 'r':
					/* 12 hour time with AM/PM: hh:mm:ss XM */
					strftime(buffer,
								(size_t) sizeof buffer,
								"%I:%M:%S %p",
								&user_tm);
					break;

				case 'R':
					/* 24 hour time: hh:mm */
					strftime(buffer,
								(size_t) sizeof buffer,
								"%H:%M",
								&user_tm);
					break;

			   /* INDIVIDUAL DATE AND TIME PLACEHOLDERS */

				case '%':
					/* Literal percent sign */
					strcpy(buffer, "%");
					break;

				case 'A':
					/* Full weekday name */
					strcpy(buffer, weekday[user_tm.tm_wday]);
					break;

				case 'a':
					/* Three letter weekday */
					sprintf(buffer, "%3.3s", weekday[user_tm.tm_wday]);
					break;

				case 'w':
					/* Day week as number, 0-6 */
					sprintf(buffer, "%d", user_tm.tm_wday);
					break;

				case 'u':
					/* Day week as number, 1-7 */
					sprintf(buffer, "%d", user_tm.tm_wday + 1);
					break;

				case 'd':
					/* Day of the month w/leading zero */
					sprintf(buffer, "%02d", user_tm.tm_mday);
					break;

				case 'e':
					/* Day of the month NO leading zero */
					sprintf(buffer, "%2d", user_tm.tm_mday);
					break;

				case 'B':
					/* Full name of month */
					strcpy(buffer, month[user_tm.tm_mon]);
					break;

				case 'b':
					/* Three letter name of month */
					sprintf(buffer, "%3.3s", month[user_tm.tm_mon]);
					break;

				case 'm':
					/* Numeric month */
					sprintf(buffer, "%02d", user_tm.tm_mon + 1);
					break;

				case 'Y':
					/* Four digit year */
					sprintf(buffer, "%04d", (user_tm.tm_year + 1900));
					break;

				case 'y':
					/* Two digit year */
					sprintf(buffer, "%02d", (user_tm.tm_year + 1900) % 100);
					break;

				case 'H':
					/* Hour on 24-hour clock */
					sprintf(buffer, "%02d", user_tm.tm_hour);
					break;

				case 'k':
					/* Hour on 24-hour clock. no leading zero */
					sprintf(buffer, "%02d", user_tm.tm_hour);
					break;

				case 'I':
					/* 12 hour clock hour of day */
					if (user_tm.tm_hour % 12 == 0) {
						strcpy(buffer, "12");
					} else {
						sprintf(buffer, "%02d", user_tm.tm_hour % 12);
					}
					break;

				case 'p':
					/* AM/PM */
					strcpy(buffer, user_tm.tm_hour < 12 ? "AM": "PM");
					break;

				case 'P':
					/* am/pm */
					strcpy(buffer, user_tm.tm_hour < 12 ? "am": "pm");
					break;

				case 'M':
					/* Minute */
					sprintf(buffer, "%02d", user_tm.tm_min);
					break;

				case 'S':
					/* Second */
					sprintf(buffer, "%02d", user_tm.tm_sec);
					break;

				case 'f':
					/* Microsecond */
					sprintf(buffer, "%06ld", tv.tv_usec); 
					if (is_unique_time) {
						fprintf(stderr,
							"%s %ld.%06ld %s (%s)",
							"Current Microseconds",
							tv.tv_sec, 
							tv.tv_usec,
							" are not from same source as user specified time",
							asctime(&user_tm));
					}
					break;

				case 'Z':
					/* timezone name or abbreviation */
					sprintf(buffer, "%s", 
					is_gmt ?
						"GMT" :
						timezone(tz.tz_minuteswest, user_tm.tm_isdst));
					break;

				case 'z':
					/* Timezone offset */

					/* 
						Note the returned offset is WEST of GMT, and we want to
						represent that times EAST of GMT are positive.
					*/
					sprintf(buffer,
							  "%+05d",
							  is_gmt ?
							  0 :
							  -(tz.tz_minuteswest / 60 * 100 + tz.tz_minuteswest % 60));
					break;

				case 's':
					/* Seconds since UNIX Epoch */
					sprintf(buffer, "%ld", tv.tv_sec);
					if (is_unique_time) {
						fprintf(stderr,
							"%s %ld.%06ld %s (%s)",
							"Seconds since UNIX Epoch",
							tv.tv_sec, 
							tv.tv_usec,
							" are not from same source as user specified time",
							asctime(&user_tm));
					}
					break;

				case 'j':
					/* Day of year (julian day) to IBM OS/360 refugees)	*/
					sprintf(buffer, "%3ld", user_tm.tm_yday + 1);
					break;

				case 't': 
					/* tab (GNU) */
					strcpy(buffer, "\t");
					break;

				case 'n':
					/* Newline (GNU) */
					strcpy(buffer, "\n");
					break; 

			/* All dash-prefixed individual placeholders omit leading zero */

				case '-':
					switch(format[column++]) {
						case 'm':
							/* Numeric month */
							sprintf(buffer, "%2d", user_tm.tm_mon + 1);
							break;

						case 'y':
							/* Two digit year */
							sprintf(buffer, "%2d", (user_tm.tm_year + 1900) % 100);
							break;

						case 'I':
							/* 12 hour clock hour of day */
							if (user_tm.tm_hour % 12 == 0) {
								strcpy(buffer, "12");
							} else {
								sprintf(buffer, "%2d", user_tm.tm_hour % 12);
							}
							break;

						case 'M':
							/* Minute */
							sprintf(buffer, "%2d", user_tm.tm_min);
							break;

						case 'S':
							/* Second */
							sprintf(buffer, "%2d", user_tm.tm_sec);
							break;

						default:
							fprintf(stderr,
										  "Invalid prefixed format '%c' at column %d of: \"%s\"\n",
										  format[column],
										  column - 1,
										  format);
							abort();
							break;

					} /* (inner) switch */
					break;

				default:
					fprintf(stderr,
									"Unimplemented format '%c' at column %d of: \"%s\"\n",
									format[column - 1],
									column - 1,
									format);
					abort();
					break;

			} /* (outer) switch */


#ifdef DEBUG 
			printf("Columnn %2d pattern '%c'.\t", column, format[column - 1]);
#endif
			

		} /*  if ('%' == format[column++]) */
		else {
			/* Not part of a format spec, just copy literal char	*/
			buffer[0] = format[column - 1];
			buffer[1] = '\0';

#ifdef DEBUG 
			printf("Columnn %2d literal '%s'.\t", column, buffer);
#endif
		}

		/* Add whatever we copied/generated from our buffer to user result */

		if ((used + strlen(buffer) + 1) < result_size) {
			strcat((char *) result, (char *) buffer);
			used += strlen((char *)buffer);

#ifdef DEBUG 
			printf("Output (%d chars): \"%s\"\n", used, result);
#endif
		}
		else {
			fprintf(stderr,
				 "Output overflow at character '%c' at column %d of: \"%s\"\n",
				 format[column - 1],
				 column - 1,
				 format);
			memset(result, '\0', result_size);
			errno = ENOMEM;
			return 0;
		}

	} /* while */

	/* And on the __LINE__ line, he rested */
	return used;

}
