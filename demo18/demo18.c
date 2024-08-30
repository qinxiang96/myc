#include <stdio.h>
struct date{
    int month;
    int day;
    int year;
};
int main(int argc, char const *argv[]){
    struct date today = {07,31,2014};
    struct date thismonth = {.month = 7, .year = 2014};
    printf("Today's date is %i-%i-%i.\n",today.year,today.month,today.day);
    printf("this month is %i-%i-%i.\n",thismonth.year,thismonth.month,thismonth.day);
    return 0;
    //Today's date is 2014-7-31.
    //this month is 2014-7-0.


    
}