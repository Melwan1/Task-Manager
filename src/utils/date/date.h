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

/* get_elapsed_days_in_current_year
 * Returns the number of days that have elapsed in the current year.
 * The arguments are always valid, meaning that the year corresponding to the second argument,
 * according to the previous function, is always equal to the first argument.
 * 
 * For example, if the parameters are year 1971 and 500 days, which equals to 1 year and 135 days,
 * it means that 135 days have elapsed in the year 1971. So the function returns 135.
 * 
 * params: 
 *
 * - year: the current year (>= 1970)
 * - days_since_epoch: the number of days since 1970-01-01.
 *
 * return: the number of days that have elapsed in the current year.
*/

int get_elapsed_days_in_current_year(int year, int days_since_epoch);

/* fill_month_and_day
 * Fills the month and day field of the input structure.
 * This function makes use of the year already filled in the structure to compute the rest of the fields.
 * 
 * params: 
 *
 * - timestamp: the structure to be filled
 * - days_since_epoch: the number of days since 1970-01-01.
 *
 * return: void
*/

void fill_month_and_day(struct timestamp *timestamp, int days_since_epoch);

/* get_current_date
** Build a timestamp structure containing the current time.
**
** params: None
**
** return: the built timestamp strucure.
*/

struct timestamp *get_current_date(void);

void print_timestamp(struct timestamp *timestamp);

#endif /* !DATE_H */
