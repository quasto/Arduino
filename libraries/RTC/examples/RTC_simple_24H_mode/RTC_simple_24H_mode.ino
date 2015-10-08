/**********************************************************************************************************************************************************
This sketch gives a simple demonstration of how to use RTC library.
The code sets date and time using internal structure and then print on SerialUSB date and time. Time representation is 24 hour mode
**********************************************************************************************************************************************************/



#include <RTCInt.h>

RTCInt rtc;  //create an RTCInt type object


void setup() 
{
  SerialUSB.begin(9600);
  
  rtc.begin(TIME_H24); //init RTC in 12 hour mode
  
  //time settings
  rtc.setHour(23,0);  //setting hour
  rtc.setMinute(59);  //setting minute
  rtc.setSecond(40);   //setting second
  
  
  rtc.setDay(31);     //setting day
  rtc.setMonth(12);    //setting month
  rtc.setYear(15);    //setting year
  
}

void loop() 
{
 rtc.getDate();      //getting date in local structure (local_date)
 rtc.getTime();      //getting time in local structure(local_time)
 
 //printing date in format YYYY/MM/DD
 SerialUSB.print(rtc.date.year+2000); // year
 SerialUSB.print('/');
 SerialUSB.print(rtc.date.month);    // month
 SerialUSB.print('/');
 SerialUSB.print(rtc.date.day);      // day
 SerialUSB.print(' ');
 
 //printing time
 SerialUSB.print(rtc.time.hour);    //hour
 SerialUSB.print(':');
 SerialUSB.print(rtc.time.minute);  //minute
 SerialUSB.print(':');
 SerialUSB.println(rtc.time.second);  //second
 
 delay(500);
}
