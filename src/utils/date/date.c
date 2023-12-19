#include "date.h"

#include <stdlib.h>
#include <stdio.h>

#define TIMESTAMP_FIELD_NUMBER 6 // the number of fields for the timestamp structure

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
