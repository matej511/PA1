#ifndef __PROGTEST__
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#endif /* __PROGTEST__ */

//return 1 is leap year
//return 0 isnt leap year
int isLeapYear(int y){
    int leap=0;
    if(y%4==0 )
        leap=1;
    if(y%100==0)
        leap=0;
    if(y%400==0)
        leap=1;
    if(y%4000==0)
        leap=0;
    return leap;
}

/**
 * return days in month
 * @param[in] 
 * @return number of day in month
*/
int monthDays(int m,int y){
    if (m==2){
        if(isLeapYear(y)==0)
            return 28;
        else
            return 29;
    }
    if ((m <=7 && m%2==0 && m!=2 && m>0)|| (m>7 && m<=12 &&m%2!=0)){
        return 30;
    }
    if ((m <=7 && m%2!=0 && m!=2 && m>0)|| (m>7 && m<=12 && m%2==0)){
        return 31;
    }
    return 0;
}

/**
 * return number of days until start of year
 * using @isLeapYear for number of days in leap year*/
long int numberDaysByYear(int y){
    long int days=0;
    for (long int i = 1; i <y ; i++)
    {
        if(isLeapYear(i)==1)
            days+=366;
        else
            days+=365;
    }
    return days;    
}

/**
 * return number of days in the every month int the year
 * using @monthDays returning number of days in the month*/
int numberDayByMonth(int m, int y){
    int days=0;
    for(int i=1; i<m;i++){
        days+=monthDays(i,y);
    }
    return days;
}

//null time for hour
int nullHour(int h){
    int bell = 0;
    for(int i=0;i<=h; i++){
        if(i%12==0)
            bell+=12;
        else
            bell+=i%12;
    }
    return bell;
}
int nullMinute(int m){
    int bell = 4;
    for(int i=0; i<=m; i+=15){
        bell+=i/15;
    }
    return bell;
}
//null time for minutes

//control inputs
int control(int y1, int m1, int d1, int h1, int i1,
            int y2, int m2, int d2, int h2, int i2){ 
    if(y1>y2)
        return 0;
    if (m1>m2 && y1==y2)
        return 0;
    if (m1==m2 && y1==y2 && d1>d2) 
        return 0;
    if (m1==m2 && y1==y2 && d1==d2 && h1>h2)
        return 0;
    if (m1==m2 && y1==y2 && d1==d2 && h1==h2 && i1>i2)
        return 0;
    if(y1<1600 || y2<1600 || m1<1 || m1>12 || m2<1 || m2>12 ||
        d1<1 || d2<1 || h1>23 || h1<0 || h2>23 || h2<0 
        || i1<0 || i2<0 || i1>59 || i2>59){
        return 0;
    }
    if(d1>monthDays(m1,y1) ||d2>monthDays(m2,y2)){
        return 0;
    }
    return 1;   
}

void calculation (int y1, int m1, int d1, int h1, int i1,
            int y2, int m2, int d2, int h2, int i2, long long *b1, long long *b2){
    

    long long int days1= (numberDaysByYear(y1)+ numberDayByMonth(m1,y1)+d1);
    long long int days2= (numberDaysByYear(y2)+ numberDayByMonth(m2,y2)+d2);
    //sundays until the day
    long long int sunday2=((days2-1)/7);
    long long int sunday1 =((days1-1)/7);

    long long int plusHour= (days2-1)*156 + nullHour(h2)-sunday2*156;
    long long int plusMinutes= (days2 -1)*240 +(h2)*10 + nullMinute(i2)-sunday2*240;
    if(days2%7==0){
        plusHour=(days2-1)*156 -sunday2*156;
        plusMinutes=(days2 -1)*240 - sunday2*240;
    } 
    int hour=h1%12;
    if(hour==0)
        hour=12;
    if(i1!=0)
        hour=0;
    long long  int minusHour = nullHour(h1)-sunday1*156-hour;
    
    int minute=i1/15;
    if(minute==0)
        minute=4;
    if(i1%15!=0)
        minute=0;
    long long int minusMinutes=(h1)*10 + nullMinute(i1)-sunday1*240 - minute;
    if(days1%7==0){
        minusHour=-sunday1*156;
        minusMinutes=-sunday1*240;
    }
    *b2=plusHour - ((days1-1)*156 +minusHour);
    *b1=plusMinutes -((days1-1)*240 + minusMinutes);
    return;
}

int bells ( int y1, int m1, int d1, int h1, int i1,
            int y2, int m2, int d2, int h2, int i2,
            long long int * b1, long long int * b2 ){
    if(control(y1,m1,d1,h1,i1,y2,m2,d2,h2,i2)==0){
        return 0;
    }
    calculation(y1, m1, d1, h1,i1,
            y2,m2, d2,h2, i2,
            b1, b2 );
    return 1 ;
  
}

#ifndef __PROGTEST__
int main ( int argc, char * argv [] )
{
  long long int b1, b2; 
     bells ( 2087, 1, 18, 22, 55, 2087, 1, 18, 23, 50, &b1, &b2 );

  return EXIT_SUCCESS;
}
#endif /* __PROGTEST__ */