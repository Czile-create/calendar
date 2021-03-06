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
bool canout(int year, int month, int day)
{
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
    int N;
    printf("Column in each line: ");
    scanf("%d", &N);
    printf("The calendar of the year %d.\n",year);

    const char month_name[12][14] = { "January 1","February 2","March 3","April 4","May 5","June 6","July 7","Augest 8","Septemper 9","October 10","November 11","December 12" };
    for (int i=1; i<=12/N; i++) {
        for (int j=0; j<N; j++)
            printf("%-30s", month_name[i*N-N+j]);
        printf("\n");

        for (int j=0; j<N; j++)
            printf("===========================   ");
        printf("\n");
        for (int j=0; j<N; j++)
            printf("Sun Mon Tue Wed Thu Fri Sat   ");
        printf("\n");

        int day[12] = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};
        for (int j=0; j<N; j++)
            day[j]-=getmonthbeginweek(year, N*i-N+1+j);
        printf("\n");
        for (int j=0; j<6; j++) {
            for (int k=0; k<N; k++) {
                for (int l=0; l<7; l++) {
                    if (canout(year, N*i-N+1+k, day[k]))
                        printf("%3d", day[k]);
                    else 
                        printf("   ");
                    printf(" ");
                    day[k]++;
                }
                printf("  ");
            }
            printf("\n");

        }
        printf("\n");
    }
}

void findday() {
    int year, month, day, foo;
    printf("Please input a number to represent the format:\n 1. yyyy/mm/dd\n 2. mm/dd/yyyy\n 3. dd/mm/yyyy\n 4. yyyy,mm,dd\n 5. mm,dd,yyyy\n 6. dd,mm,yyyy\n");
    scanf("%d", &foo);
    switch (foo) {
        case 1: scanf("%d/%d/%d", &year, &month, &day);break;
        case 2: scanf("%d/%d/%d", &month, &day, &year);break;
        case 3: scanf("%d/%d/%d", &day, &month, &year);break;
        case 4: scanf("%d,%d,%d", &year, &month, &day);break;
        case 5: scanf("%d,%d,%d", &month, &day, &year);break;
        case 6: scanf("%d,%d,%d", &day, &month, &year);break;
        default: printf("NOT such command!\n");
    }
    int month_days[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    char week[7][4] = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};
    if (isleapyear(year))
        month_days[1]=29;           //处理闰年
    int ans=getyearbeginweek(year);
    for (int i=0;i<month-1;i++) 
        ans+=month_days[i];
    ans+=day-1;
    printf("The %d(th) Week, %s\n", ans/7+1, week[ans%7]);
}


int main()
{
    printf("Please choose the function: \n1. To print the Calendar;\n2. To find a day.\n");
    int foo;
    scanf("%d", &foo);
    if (foo==1) {
        printf("Please input the year: ");
        int year;
        scanf("%d", &year);
        printyear(year);
    } else if (foo==2) {
        findday();
    } else 
        printf("NOT such command!\n");
    return 0;
}
