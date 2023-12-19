#include "date.h"

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TIMESTAMP_FIELD_NUMBER                                                 \
    6 // the number of fields for the timestamp structure
#define SECONDS_IN_1_DAY 86400
#define DAYS_IN_1_YEAR 365
#define EPOCH_YEAR 1970

int days_in_year(int year)
{
    return DAYS_IN_1_YEAR + (!(year % 4) && ((year % 100) || !(year % 400)));
}

static void print_error_bad_date_format(void)
{
    char *error_string =
        "task_manager: build_timestamp: bad date format.\nUsage: "
        "year-month-day hour:minute:second\nConditions: \n\t 2000 <= year <= "
        "2100\n\t 1 <= month <= 12\n\t 1 <= day <= (28|30|31) (depends on the "
        "month)\n\t 0 <= hour <= 23\n\t 0 <= minute <= 59\n \t 0 <= second <= "
        "59\n";
    fprintf(stderr, error_string);
}

int verify_within_range(int to_test, int lower_bound, int higher_bound)
{
    return ((to_test >= lower_bound) && (to_test <= higher_bound));
}

int verify_timestamp(struct timestamp *timestamp, int tokens_scanned)
{
    int days_in_month[12] = {31, 28 + !(timestamp->year % 4), 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}; // February has 29 days if the year is a leap year, 28 otherwise.
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
    if (!verify_within_range(timestamp->day, 1,
                             days_in_month[timestamp->month - 1]))
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
    int tokens_scanned = sscanf(
        date, "%d-%d-%d %d:%d:%d", &(new_timestamp->year),
        &(new_timestamp->month), &(new_timestamp->day), &(new_timestamp->hour),
        &(new_timestamp->minute), &(new_timestamp->second));

    if (!verify_timestamp(new_timestamp, tokens_scanned))
    {
        print_error_bad_date_format();
        free(new_timestamp);
        return NULL;
    }
    return new_timestamp;
}

static int days_to_year_rec(int days, int current_year)
{
    int days_in_current_year = days_in_year(current_year); // 365 if the year is not a leap year, 366 if it is.
    if (days < days_in_current_year)
    {
        return current_year;
    }
    return days_to_year_rec(days - days_in_current_year, current_year + 1);
}

int days_to_year(int days)
{
    return days_to_year_rec(days, EPOCH_YEAR);
}

static int get_elapsed_days_in_current_year_rec(int year, int days_since_epoch)
{
    if (year == EPOCH_YEAR)
    {
        return days_since_epoch;
    }
    return get_elapsed_days_in_current_year_rec(year - 1, days_since_epoch - days_in_year(year));
}

int get_elapsed_days_in_current_year(int year, int days_since_epoch)
{
    return get_elapsed_days_in_current_year_rec(year, days_since_epoch);
}

void fill_month_and_day(struct timestamp *timestamp,
                               int days_since_epoch)
{
    int day_number_in_current_year =
        get_elapsed_days_in_current_year(timestamp->year, days_since_epoch)
        + 1; // has to be 365 (366 if leap year) or less
    int days_in_month[12] = { 31, 28 + (!(timestamp->year % 4) && ((timestamp->year % 100) || !(timestamp->year % 400))),
                              31, 30,
                              31, 30,
                              31, 31,
                              30, 31,
                              30, 31 };
    int month = 1;
    int result_day = day_number_in_current_year;
    while (result_day > days_in_month[month - 1])
    {
        result_day -= days_in_month[month - 1];
        month++;
    }
    timestamp->month = month;
    timestamp->day = result_day;
    return;
}

struct timestamp *get_current_date(void)
{
    struct timestamp *new_timestamp = malloc(sizeof(*new_timestamp));
    if (!new_timestamp)
    {
        fprintf(stderr,
                "task_manager: get_current_date: insufficient memory\n");
        return NULL;
    }
    size_t current_time =
        time(NULL); // int would be fine until Jan 19, 2038 when UNIX timestamp
                    // will exceed int capacity.
    size_t max_size_t = -1;
    if (current_time == max_size_t)
    {
        fprintf(stderr,
                "task_manager: get_current_date: couldn't get current_time");
        free(new_timestamp);
        return NULL;
    }

    int days_since_epoch = current_time / SECONDS_IN_1_DAY;

    new_timestamp->year = days_to_year(days_since_epoch);
    fill_month_and_day(new_timestamp, days_since_epoch);
    new_timestamp->second = (current_time % 60);
    new_timestamp->minute = (current_time % 3600) / 60;
    new_timestamp->hour = (current_time % 86400) / 3600;

    return new_timestamp;
}
