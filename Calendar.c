#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

//获取每一年第一天是周几
int getyearbeginweek(int year)
{
    return ((year-1)+(year-1)/4-(year/100)+(year/400)+1)%7;
}

//判断这一年是否是闰年
bool isleapyear(int year)
{
    if (!(year%400))
        return true;
    if (!(year%100))
        return false;
    if (!(year%4))
        return true;
    return false;
}

//获取每个月第一天周几
int getmonthbeginweek(int year, int month)
{
    int month_days[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if (isleapyear(year))
        month_days[1]=29;           //处理闰年
    int ans=getyearbeginweek(year); //这一年第一天是星期几
    for (int i=0; i<month-1; i++) {
        ans+=month_days[i];
        ans%=7;
    }
    return ans;
}
bool canout(int year, int month, int day) {
    int month_days[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if (isleapyear(year))
        month_days[1]=29;           //处理闰年
    if (day<=0)
        return false;
    if (day>month_days[month-1])
        return false;
    return true;
}

void printyear(int year)
{
    printf("The calendar of the year %d.\n",year);
    const char month_name[12][14] = { "January 1","February 2","March 3","April 4","May 5","June 6","July 7","Augest 8","Septemper 9","October 10","November 11","December 12" };
    for (int i=1; i<=6; i++) {
        printf("%-30s%s\n", month_name[2*i-2], month_name[2*i-1]);
        printf("===========================   ===========================\n");
        printf("Sun Mon Tue Wed Thu Fri Sat   Sun Mon Tue Wed Thu Fri Sat\n");
        int tmp1=1, tmp2=1;
        tmp1-=getmonthbeginweek(year, 2*i-1);
        tmp2-=getmonthbeginweek(year, 2*i);
        printf("\n");
        for (int j=0; j<6; j++) {
            //处理左边那一列
            for (int k=0; k<7; k++) {
                if (canout(year, 2*i-1, tmp1))
                    printf("%3d", tmp1);
                else 
                    printf("   ");
                printf(" ");
                tmp1++;
            }
            printf("  ");
            //处理右边那一列
            for (int k=0; k<7; k++) {
                if (canout(year, 2*i, tmp2))
                    printf("%3d", tmp2);
                else 
                    printf("   ");
                printf(" ");
                tmp2++;
            }
            printf("\n");
        }
    }
}

int main()
{
    printf("Please input the year: ");
    int year;
    scanf("%d", &year);
    printyear(year);
    return 0;
}
