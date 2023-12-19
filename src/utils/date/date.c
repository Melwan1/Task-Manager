#include "date.h"

#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>

#define TIMESTAMP_FIELD_NUMBER 6 // the number of fields for the timestamp structure
#define SECONDS_IN_1_DAY 86400
#define DAYS_IN_1_YEAR 365
#define EPOCH_YEAR 1970

static void print_error_bad_date_format(void)
{
    char *error_string = "task_manager: build_timestamp: bad date format.\n 
                            Usage: year-month-day hour:minute:second\n
                            Conditions: \n
                            \t 2000 <= year <= 2100\n 
                            \t 1 <= month <= 12\n
                            \t 1 <= day <= (28|30|31) (depends on the month)\n
                            \t 0 <= hour <= 23\n
                            \t 0 <= minute <= 59\n 
                            \t 0 <= second <= 59\n";
    fprintf(stderr, error_string);
}

static int verify_within_range(int to_test, int lower_bound, int higher_bound)
{
    return ((to_test >= lower_bound) && (to_test <= higher_bound));
}

static int verify_timestamp(struct timestamp *timestamp, int tokens_scanned)
{
    int days_in_month[12] = {31, 28 + !(timestamp->year % 4), 31, 30, 31, 30, 31, 31, 30, 31, 30, 31} // February has 29 days if the year is a leap year, 28 otherwise.
    if (tokens_scanned != TIMESTAMP_FIELD_NUMBER)
    {
        return 0;
    }
    if (!verify_within_range(timestamp->year, 2000, 2100))
    {
        return 0;
    }
    if (!verify_within_range(timestamp->month, 1, 12))
    {
        return 0;
    }
    if (!verify_within_range(timestamp->day, 1, days_in_month(timestamp->month - 1)))
    {
        return 0;
    }
    if (!verify_within_range(timestamp->hour, 0, 23))
    {
        return 0;
    }
    if (!verify_within_range(timestamp->minute, 0, 59))
    {
        return 0;
    }
    if (!verify_within_range(timestamp->second, 0, 59))
    {
        return 0;
    }
    return 1;
}

struct timestamp *build_timestamp(char *date)
{
    struct timestamp *new_timestamp = malloc(sizeof(*new_timestamp));
    if (!new_timestamp)
    {
        fprintf(stderr, "task_manager: build_timestamp: insufficient memory\n");
        return NULL;
    }
    int tokens_scanned = sscanf(date, "%d-%d-%d %d:%d:%d",
           &(new_timestamp->year),
           &(new_timestamp->month),
           &(new_timestamp->day),
           &(new_timestamp->hour),
           &(new_timestamp->minute),
           &(new_timestamp->second));
    
    if (!verify_timestamp(new_timestamp, tokens_scanned))
    {
        print_error_bad_date_format();
    }
    return new_timestamp;
}

struct timestamp *get_current_date(void)
{
    struct timestamp *new_timestamp = malloc(sizeof(*new_timestamp));
    if (!new_timestamp)
    {
        fprintf(stderr, "task_manager: get_current_date: insufficient memory\n");
        return NULL;
    }
    size_t current_time = time(NULL); // int would be fine until Jan 19, 2038 when UNIX timestamp will exceed int capacity.
    if (current_time == -1)
    {
        fprintf(stderr, "task_manager: get_current_date: couldn't get current_time");
        free(new_timestamp);
        return NULL;
    }

    int days_since_epoch = current_time / SECONDS_IN_DAY;

    new_timestamp->year = days_to_year(days_since_epoch);
    new_timestamp->month = get_month(new_timestamp->year, days_since_epoch);
    new_timestamp->day = get_day(new_timestamp->year, new_timestamp->month, days_since_epoch);
    new_timestamp->second = (current_time % 60);
    new_timestamp->minute = (current_time % 3600) / 60;
    new_timestamp->hour = (current_time % 86400) / 3600;

    return new_timestamp;
}
