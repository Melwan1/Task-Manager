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
