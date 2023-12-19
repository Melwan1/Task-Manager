#include "date.h"

#include <stdlib.h>
#include <stdio.h>

#define TIMESTAMP_FIELD_NUMBER 6 // the number of fields for the timestamp structure

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
    return new_timestamp;
}
