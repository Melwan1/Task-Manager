#include <criterion/criterion.h>
#include <criterion/redirect.h>

TestSuite(days_in_year_suite);

void check_days_in_year(int year, int expected)
{
    int actual = days_in_year(year);
    cr_expect_eq(actual, expected, "Expected: %d. Got: %d.", expected, actual);
}

