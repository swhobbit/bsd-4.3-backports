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

#include <ctype.h>
#include <memory.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

char  *timezone();

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
	char *number_fmt = NULL;
	size_t column = 0;
	size_t used = 0;
	size_t i;									/* GOD is REAL unless declared INTEGER */
	unsigned short is_unique_time;		/* Does current time match user time? */
	unsigned short is_gmt;					/* User requested GMT time zone */
	unsigned short upper_case_result;
	unsigned short swap_case_result;

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

			/*
				Look for an optional prefix numeric format character for
				two digit numeric fields. (GNU extension)

				Note that if any of the prefixes are used on an unsupported
				action character (composite, string, domain n<10 or n>99),
				the prefix and its format are silently ignored.
			*/


			upper_case_result = 0;
			swap_case_result = 0;
	
			switch(format[column]) {

				case '^':
					/* Upper case result */
					upper_case_result = 1;
					column++;		/* Step to action char */
					break;

				case '#':
					/* Swap case of result, mostly good for TZ */
					swap_case_result = 1;
					column++;		/* Step to action char */
					break;

				case '-':
					/* No padding */	
					number_fmt = "%d";
					column++;		/* Step to action char */
					break;

				case '_':
					/* Space padding if needed */
					number_fmt = "%2d";
					column++;		/* Step to action char */
					break;

				case '0':
					/* Zero padding if needed */
					number_fmt = "%02d";
					column++;		/* Step to action char */
					break;

				default:
					/*
						No padding character. Treat as zero pad but don't
						advance the column -- the current column is already
						the action character. 	
					*/
					number_fmt = "%02d";
					break;
			}

  			/* Pick a conversion character and act on it. */

			switch(format[column++]) {

						/* PRE-FORMATTED DATE AND TIME STRINGS */

				/*
					Note: All result strings built from the compound date &
							time strings are short enough compared to the
							internal buffer that there is no need to check
							nested strftime() calls for overflow.
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
					/* 'X' is locale dependent time, assumes USA: hh:mm:ss */
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
					sprintf(buffer, number_fmt, user_tm.tm_mday);
					break;

				case 'e':
					/* Day of the month NO leading zero */
					sprintf(buffer, "%d", user_tm.tm_mday);
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
					sprintf(buffer, number_fmt, user_tm.tm_mon + 1);
					break;

				case 'Y':
					/* Four digit year */
					sprintf(buffer, "%04d", (user_tm.tm_year + 1900));
					break;

				case 'y':
					/* Two digit year */
					sprintf(buffer, number_fmt, (user_tm.tm_year + 1900) % 100);
					break;

				case 'H':
					/* Hour on 24-hour clock */
					sprintf(buffer, number_fmt, user_tm.tm_hour);
					break;

				case 'k':
					/* Hour on 24-hour clock. no leading zero */
					sprintf(buffer, "%d", user_tm.tm_hour);
					break;

				case 'I':
					/* 12 hour clock hour of day */
					if (user_tm.tm_hour % 12 == 0) {
						strcpy(buffer, "12");
					} else {
						sprintf(buffer, number_fmt, user_tm.tm_hour % 12);
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
					sprintf(buffer, number_fmt, user_tm.tm_min);
					break;

				case 'S':
					/* Second */
					sprintf(buffer, number_fmt, user_tm.tm_sec);
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

				case '\0':
					/* Premature end of the template. Fatal! */
					fprintf(stderr,
							  "Incomplete format at end of template: \"%s\"\n",
							  format);
					abort();
					break;

				default:
					/* Bad template. Fatal! */
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

		/* Perform requested icase transformations */

		if (upper_case_result) {
			for (i = 0; i < strlen(buffer); i++) {
				if (isascii(buffer[i]) && islower(buffer[i])) {
					buffer[i] = toupper(buffer[i]);
				}
			}
		} else if (swap_case_result) {
			for (i = 0; i < strlen(buffer); i++) {

				/* Swap case of each alpahbetic character */

				if (isascii(buffer[i]) && islower(buffer[i])) {
					buffer[i] = toupper(buffer[i]);
				}  else if (isascii(buffer[i]) && isupper(buffer[i])) {
					buffer[i] = tolower(buffer[i]);
				}
			}
		}


		/* Add data copied/generated from our buffer to user result */

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
			return 0;
		}

	} /* while */

	/* And on the __LINE__ line, he rested */
	return used;

}
