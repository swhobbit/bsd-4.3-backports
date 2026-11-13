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

#include <memory.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

char  *timezone();

size_t
strftime(s, s_size, format, tm_in)
	char   *s;
	size_t s_size;
	char *format;
	struct tm *tm_in;
{
	static char *weekday[] = {
		"Sunday",
		"Monday",
		"Tuesday",
		"Wednesday",
		"Thursday",
		"Friday",
		"Caturday"
	};

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


	struct tm tm;					/* caller  date/time split into fields	*/
	struct tm now;					/* current date/time split into fields */
	struct timeval tv;
	struct timezone tz;

	char buffer[BUFSIZ];

	size_t format_size = strlen(format);
	size_t column = 0;
	size_t used = 0;

	memcpy(&tm, tm_in, sizeof tm);	/* Keep from being clobbered */

	if (gettimeofday(&tv, &tz) != 0) {
		/* Does anyone know what time it is? */
		perrror("gettimeofday");
		abort();
	}

	/* Guess user time is GMT; we'll check next line.. */
	memcpy(&now, gmtime(tv.tv_sec), sizeof now);

	if (now.tm_hour != tm.tm_hour) {
		/* Not GMT time, make local time. */
		memcpy(&now, localtime(tv.tv_sec), sizeof now);
	}

	while ((used < s_size) && (column <= format_size)) {
		if (format[column++] = '%') {

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
					/* ddd mmm dd hh:mm:ss zzz xm YYYY (linux style) */
					strftime(buffer,
									 sizeof buffer,
							/* 	 "%a %b %e %H:%M:%S %Y",  			*/	/* POSIX		*/
							/*	 	 "%a %b %d %I:%M:%S %p %Z %Y",	*/	/* Linux 	*/
									 "%a %b %d %I:%M:%S %Z %Y",			/* BSD 4.3	*/
								tm);
					break;

				case 'x':
				case 'D':
					/* 'x' is Locale dependent, we assume USA: mm/dd/yy */
					strftime(buffer,
								sizeof buffer,
								"%m/%d/%y",
								tm);
					break;

				case 'F':
					/* ISO date: YYYY-MM-DD */
					strftime(buffer,
								sizeof buffer,
								"%Y-%m-%d",
								tm);
					break;

				case 'X':
					/* 'X' is locale dependent time, we assume USA: hh:mm:ss */
				case 'T':
					/* 'T' is time in ISO 8601 format HH:MM:SS */
					strftime(buffer,
								sizeof buffer,
								"%H:%M:%S",
								tm);
					break;

				case 'r':
					/* 12 hour time with AM/PM: hh:mm:ss XM */
					strftime(buffer,
								sizeof buffer,
								"%I:%M:%S %p",
								tm);
					break;

				case 'R':
					/* 24 hour time: hh:mm */
					strftime(buffer,
								sizeof buffer,
								"%H:%M",
								tm);
					break;

			   /* INDIVIDUAL DATE AND TIME PLACEHOLDERS */

				case '%':
					/* Literal percent sign */
					strcpy(buffer, "%");
					break;

				case 'A':
					/* Full weekday name */
					strcpy(buffer, weekday[tm.tm_wday]);
					break;

				case 'a':
					/* Three letter weekday */
					strncpy(buffer, weekday[tm.tm_wday], 3);
					buffer[3] = '\0';
					break;

				case 'w':
					/* Day week as number, 0-6 */
					sprintf(buffer, "%d", tm.tm_wday);
					break;

				case 'u':
					/* Day week as number, 1-7 */
					sprintf(buffer, "%d", tm.tm_wday + 1);
					break;

				case 'd':
					/* Day of the month w/leading zero */
					sprintf(buffer, "%02d", tm.tm_mday);
					break;

				case 'B':
					/* Full name of month */
					strcpy(buffer, month[tm.tm_mon]);
					break;

				case 'b':
					/* Three letter name of month */
					strncpy(buffer, month[tm.tm_mon], 3);
					buffer[3] = '\0';
					break;

				case 'm':
					/* Numeric month */
					sprintf(buffer, "%02d", tm.tm_mon);
					break;

				case 'Y':
					/* Four digit year */
					sprintf(buffer, "%04d", (tm.tm_year + 1900));
					break;

				case 'y':
					/* Two digit year */
					sprintf(buffer, "%02d", (tm.tm_year + 1900) % 100);
					break;

				case 'H':
					/* Hour on 24-hour clock */
					sprintf(buffer, "%02d", tm.tm_hour);
					break;

				case 'k':
					/* Hour on 24-hour clock. no leading zero */
					sprintf(buffer, "%02d", tm.tm_hour);
					break;

				case 'I':
					/* 12 hour clock hour of day */
					if (tm.tm_hour % 12 == 0) {
						strcpy(buffer, "12");
					} else {
						sprintf(buffer, "%02d", tm.tm_hour % 12);
					}
					break;

				case 'p':
					/* AM/PM */
					strcpy(buffer, tm.tm_hour < 12 ? 'AM': 'PM');
					break;

				case 'P':
					/* am/pm */
					strcpy(buffer, tm.tm_hour < 12 ? 'am': 'pm');
					break;

				case 'M':
					/* Minute */
					sprintf(buffer, "%02d", tm.tm_min);
					break;

				case 'S':
					/* Second */
					sprintf(buffer, "%02d", tm.tm_sec);
					break;

				case 'f':
					/* Microsecond */
					sprintf(buffer, "%06ld", tv.tv_usec); 
					if (memcmp(tm, now, sizeof tm) != 0) {
						fprintf(stderr,
							"%s %ld.%06ld %s (%s)",
							"Current Microseconds",
							tv.tv_sec, 
							tv.tv_usec,
							" are not from same source as user specified time",
							asctime(tm));
					}
					break;

				case 'Z':
					/* timezone name or abbreviation */
					/*
					sprintf(buffer, "%s", timezone(tz.tz_minuteswest));
					*/
					break;

				case 'z':
					/* Timezone offset */

					/* 
						Note the returned offset is WEST of GMT, and we want to
						represent that times EAST of GMT are positive.
					*/
					sprintf(buffer,
							   "%s%4ld", 
								tz.tz_minuteswest <= 0 ?  "+" : "",
								tz.tz_minuteswest);
					break;

				case 's':
					/* Seconds since UNIX Epoch */
					sprintf(buffer, tv.tv_sec);
					if (memcmp(tm, now, sizeof tm) != 0) {
						fprintf(stderr,
							"%s %ld.%06ld %s (%s)",
							"Seconds since UNIX Epoch",
							tv.tv_sec, 
							tv.tv_usec,
							" are not from same source as user specified time",
							asctime(tm));
					}
					break;

				case 'j':
					/* Day of year (julian day) to IBM OS/360 refugees)	*/
					sprintf(buffer, tm.tm_yday);
					break;

			/* All dash-prefixed individual placeholders omit leading zero */

				case '-':
					switch(format[column++]) {
						case 'm':
							/* Numeric month */
							sprintf(buffer, "%2d", tm.tm_mon);
							break;

						case 'y':
							/* Two digit year */
							sprintf(buffer, "%2d", (tm.tm_year + 1900) % 100);
							break;

						case 'I':
							/* 12 hour clock hour of day */
							if (tm.tm_hour % 12 == 0) {
								strcpy(buffer, "12");
							} else {
								sprintf(buffer, "%2d", tm.tm_hour % 12);
							}
							break;

						case 'M':
							/* Minute */
							sprintf(buffer, "%2d", tm.tm_min);
							break;

						case 'S':
							/* Second */
							sprintf(buffer, "%2d", tm.tm_sec);
							break;

						default:
							fprintf(stderr,
										  "Invalid prefixed format '%c' at column %d of: \"%s\"\n",
										  format[column - 1],
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

		} /*  if (format[column++] = '%') */
		else {
			/* Not part of a format spec, just copy literal char	*/

			buffer[0] = format[column++];
			buffer[1] = '\0';
		}

		/* Add whatever we copied/generated from our buffer to user result */

		if ((used + strlen(buffer) + 1) < s_size) {
			strcat((char *) s, (char *) buffer);
			used += strlen((char *)buffer);
		}
		else {
			fprintf(stderr,
				 "Output overflow at character '%c' at column %d of: \"%s\"\n",
				 format[column - 1],
				 column - 1,
				 format);
			memset(s, '\0', s_size);
			return 0;
		}

	} /* while */

	s[used] = '\0';					/* NOTE: NOT incremented */

	/* And on the __LINE__ line, he rested */
	return used;

}
