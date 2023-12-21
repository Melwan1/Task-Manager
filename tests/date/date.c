#include <criterion/criterion.h>
#include <criterion/redirect.h>

#include "../../src/utils/date/date.h"

TestSuite(days_in_year_suite);

void check_days_in_year(int year, int expected)
{
    int actual = days_in_year(year);
    cr_expect_eq(actual, expected, "Expected: %d. Got: %d.", expected, actual);
}

Test(days_in_year_suite, days_in_year_1)
{
    check_days_in_year(2000, 366);
}

Test(days_in_year_suite, days_in_year_2)
{
    check_days_in_year(2001, 365);
}

Test(days_in_year_suite, days_in_year_3)
{
    check_days_in_year(2002, 365);
}

Test(days_in_year_suite, days_in_year_4)
{
    check_days_in_year(2003, 365);
}

Test(days_in_year_suite, days_in_year_5)
{
    check_days_in_year(2004, 366);
}

Test(days_in_year_suite, days_in_year_6)
{
    check_days_in_year(2006, 365);
}

Test(days_in_year_suite, days_in_year_7)
{
    check_days_in_year(2008, 366);
}

Test(days_in_year_suite, days_in_year_8)
{
    check_days_in_year(2040, 366);
}

Test(days_in_year_suite, days_in_year_9)
{
    check_days_in_year(2023, 365);
}

Test(days_in_year_suite, days_in_year_10)
{
    check_days_in_year(2100, 365);
}

Test(days_in_year_suite, days_in_year_11)
{
    check_days_in_year(2048, 366);
}

Test(days_in_year_suite, days_in_year_12)
{
    check_days_in_year(2066, 365);
}

Test(days_in_year_suite, days_in_year_13)
{
    check_days_in_year(2072, 366);
}

Test(days_in_year_suite, days_in_year_14)
{
    check_days_in_year(2087, 365);
}

