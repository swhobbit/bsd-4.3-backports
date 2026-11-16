#!/bin/sh

# Abort on first error

set -e

./date $1	"+%%	%%%%	Percent sign"
./date $1	"+%t	%%t     Tab character (GNU extension)"
./date $1	"+%n	%%n     Newline chacter (GNU extension)"

echo ''

./date $1	"+%c	%%c	Thu Jan 28 12:32:01 2014   locale's (hardcoded to US) date and time"
./date $1	"+%+	%%+	Thu Jan 28 12:32:01 2014   POSIX (hardcoded to US) date and time"
./date $1	"+%D	%%D	23/05/12 formats the date as YY/MM/DD"
./date $1	"+%F	%%F	2025-12-01 locale (hardcoded to US) in ISO 8601 format YYYY-MM-DD"
./date $1	"+%x	%%x	02/10/11 locale's (hardcoded to US) appropriate date representation"
./date $1	"+%X	%%X	02/10/11 locale's (hardcoded to US) appropriate time representation"
./date $1	"+%r	%%r	3:44:12 AM  12-hour time"
./date $1	"+%R	%%R	15:21 24-hour time HH:MM"
./date $1	"+%T	%%T	15:21:59 time in ISO 8601 format HH:MM:SS (no padding change)"
./date $1	"+%0T	%%0T	15:21:59 time in ISO 8601 format HH:MM:SS (no padding change)"
./date $1	"+%-T	%%-T	15:21:59 time in ISO 8601 format HH:MM:SS (no padding change)"
./date $1	"+%_T	%%_T	15:21:59 time in ISO 8601 format HH:MM:SS (no padding change)"

echo ''

./date $1	"+%A	%%A	Monday   full weekday name"
./date $1	"+%a	%%a	Mon   abbreviated weekday name"
./date $1	"+%w	%%w	0-6   day of the week with Sunday as 0"

./date $1	"+%d	%%d	01-31 day of the month (with a leading zero)"
./date $1	"+%0d	%%0d	01-31 day of the month (with a leading zero)"
./date $1	"+%-d	%%-d	1-31 day of the month (no padding)"
./date $1	"+%_d	%%_d	1-31 day of the month (with a leading space)"
./date $1	"+%e	%%e	1-31 day of the month (no padding)"

./date $1	"+%B	%%B	April full month name"
./date $1	"+%b	%%b	Apr   abbreviated month name"
./date $1	"+%m	%%m	01-12 month of the year (with a leading zero)"
./date $1	"+%0m	%%0m	01-12 month of the year (with a leading zero)"
./date $1	"+%-m	%%-m	1-12  month of the year (no padding)"
./date $1	"+%_m	%%_m	1-12  month of the year (with a leading space)"

./date $1	"+%Y	%%Y	2003  digit year (four digits)"

./date $1	"+%y	%%y	00-99 year without a century (last two digits, with a leading zero)"
./date $1	"+%0y	%%0y	00-99 year without a century (last two digits, with a leading zero)"
./date $1	"+%-y	%%-y	0-99  year without a century (last two digits, no padding)"
./date $1	"+%_y	%%_y	0-99  year without a century (last two digits, no padding)"

./date $1	"+%H	%%H	00-23 hour of the day, 24-hour time (with a leading zero)"
./date $1	"+%0H	%%0H	00-23 hour of the day, 24-hour time (with a leading zero)"
./date $1	"+%-H	%%-H	0-23  hour of the day, 24-hour time (no padding)"
./date $1	"+%_H	%%_H	0-23  hour of the day, 24-hour time (with a leading space)"
./date $1	"+%k	%%k	0-23  hour of the day, 24-hour time (no padding)"

./date $1	"+%I	%%I	01-11 hour of the day, 12-hour time (with a leading zero)"
./date $1	"+%0I	%%0I	01-11 hour of the day, 12-hour time (with a leading zero)"
./date $1	"+%-I	%%-I	1-11  hour of the day, 12-hour time (no padding)"
./date $1	"+%_I	%%_I	1-11  hour of the day, 12-hour time (with a leading space)"

./date $1	"+%P	%%P	am, pm   am or pm designation"
./date $1	"+%p	%%p	AM, PM   AM or PM designation"

./date $1	"+%M	%%M	00-59 minute of the hour (with a leading zero)"
./date $1	"+%0M	%%0M	00-59 minute of the hour (with a leading zero)"
./date $1	"+%-M	%%-M	0-59  minute of the hour (no padding)"
./date $1	"+%_M	%%_M	0-59  minute of the hour (with a leadig space)"

./date $1	"+%S	%%S	00-60 second of the minute (with a leading zero)"
./date $1	"+%0S	%%0S	00-60 second of the minute (with a leading zero)"
./date $1	"+%-S	%%-S	0-60  second of the minute (no padding)"
./date $1	"+%_S	%%_S	0-60  second of the minute (with a leading space)"

./date $1	"+%f	%%f	000000-999999  microsecond of the second (with leading zeroes)"

./date $1	"+%Z	%%Z	UTC   timezone name or abbreviation"
./date $1	"+%z	%%z	+0000 UTC offset in the form +HHMM or -HHMM"
./date $1	"+%s	%%s	amount of seconds since 1970-01-01 00:00:00 UTC"
./date $1	"+%j	%%j	001-366  day of the year (with leading zeroes)"

echo  ''

# Not implemented
# ./date $1	"+%U	%%U	00-53 week number with the first Sunday as the first day of week one"
# ./date $1	"+%W	%%W	00-53 week number of the current year, starting with the first Monday as the first day of the first week"
# ./date $1	"+%V	%%V	01-53 week number in ISO 8601 format"

exit $?
