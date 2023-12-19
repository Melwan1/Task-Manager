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

/* verify_timestamp
** Checks whether a timestamp is valid.
** A timestamp is valid if all 6 tokens (year, month, day, hour, minute, second) have successfully been scanned,
** and if all associated integers fall within their respective range.
** - year : between 2000 and 2100,
** - month : between 1 and 12,
** - day: between 1 and the number of days in the month above,
** - hour: between 0 and 23,
** - minute: between 0 and 59,
** - second: between 0 and 59.
**
** params: 
**
** - timestamp: the timestamp structure to be tested,
** - tokens_scanned: the number of tokens scanned by scanf-like function.
** 
** return: true if the timestamp is valid, false otherwise.
*/

int verify_timestamp(struct timestamp *timestamp, int tokens_scanned);

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

/* days_to_year
 * Returns the year corresponding to the epoch days given as parameter. The epoch is 1970-01-01 00:00:00.
 * For example, if the parameter is 500, which is 1 year and 135 days, the year is 1971.
 *
 * params:
 * 
 * - days: the number of days since the epoch.
 *
 * return: the year corresponding to the number of days since the epoch.
*/

int days_to_year(int days);

/* get_current_date
** Build a timestamp structure containing the current time.
**
** params: None
**
** return: the built timestamp strucure.
*/

struct timestamp *get_current_date(void);

#endif /* !DATE_H */
