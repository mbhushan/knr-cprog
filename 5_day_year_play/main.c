#include <stdio.h>

static char daytab[2][13] = {
        {0, 31,28,31,30,31,30,31,31, 30, 31,30, 31},
        {0, 31,29,31,30,31,30,31,31, 30, 31,30, 31}
};

/* day_of_year: set day of year from month and day */
int day_of_year(int year, int month, int day) {
    int i, leap;
    leap = year%4 == 0 && year%100 != 0 || year%400 == 0;
    for (i=1; i<month; i++) {
        day += daytab[leap][i];
    }
    return day;
}

/* month_day: set month, day from day of the year */
void month_day(int year, int yearday, int *pmonth, int *pday) {
    int i, leap;
    leap = year % 4 == 0 && year % 100 != 0 || year%400 == 0;
    for (i=1; yearday > daytab[leap][i]; i++){
        yearday -= daytab[leap][i];
    }
    *pmonth = i;
    *pday = yearday;
}

int main() {
    int pmonth = 0, pday = 0;
    printf("day of year for 8jan2013: %d\n", day_of_year(2013, 1, 8));
    printf("day of year for 10aug2018: %d\n", day_of_year(2018, 8, 10));
    printf("day of year for 25nov1983: %d\n", day_of_year(1983, 11, 25));
    printf("day of year for 12dec1983: %d\n", day_of_year(1983, 12, 12));

    month_day(2021, 300, &pmonth, &pday);
    printf("month_day for day 300 month/day: %d // %d\n ", pmonth, pday);
    return 0;
}
