#ifndef DATE_H
#define DATE_H

struct timestamp
{
    int year;
    int month;
    int day;
    int hour;
    int minute;
    int second;
};

/* days_in_year
** Gives the number of days in the input year. Returns 365 if the year is not a leap year and 366 if it is.
** A leap year is divisible by 4 but not by 100. The leap years in the current century are
** 2004, 2008, 2012 ... 2092, 2096, but not 2100.
**
** params:
**
** - year: the year number to calculate the days on.
**
** return: the number of days within that year.
*/

int days_in_year(int year);

/* verify_within_range
** Returns true if the input number is within the range given by the other parameters, false otherwise.
**
** params: 
**
** - to_test: the number to verify whether it falls in the range,
** - lower_bound: the lower bound of the range,
** - higher_bound: the higher bound of the range.
**
** return: the boolean described above.
*/

int verify_within_range(int to_test, int lower_bound, int higher_bound);

/* build_timestamp 
** Build a timestamp structure from a string date.
**
** params:
**
** - date: string representing the date to be formatted. The date must follow the pattern "YYYY-MM-DD HH:MM:SS"
**
** return: the built timestamp structure.
*/

struct timestamp *build_timestamp(char *date);

/* get_current_date
** Build a timestamp structure containing the current time.
**
** params: None
**
** return: the built timestamp strucure.
*/

struct timestamp *get_current_date(void);

#endif /* !DATE_H */
