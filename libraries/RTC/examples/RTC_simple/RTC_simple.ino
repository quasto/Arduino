/**********************************************************************************************************************************************************
This sketch gives a simple demonstration of how to use RTC library.
The code sets date and time using internal structure and then print on SerialUSB date and time. Time representation is 12 hour mode
**********************************************************************************************************************************************************/



#include <RTCInt.h>

RTCInt rtc;  //create an RTCInt type object


void setup() 
{
  SerialUSB.begin(9600);
  while(!SerialUSB);
  rtc.begin(TIME_H12); //init RTC in 12 hour mode
  
  //filling internal structure for time
  rtc.time.hour = 11;          //hour
  rtc.time.minute = 59;       //minute
  rtc.time.second = 40;        //second
  rtc.time.Tmode = POST_MERIDIAN;  
  
  //filling internal structure for date
  rtc.date.day = 31;        //day
  rtc.date.month = 12;       //month
  rtc.date.year = 15;       //year
  
  rtc.setTime();  //setting time
  rtc.setDate();  //setting date
  
  
  
  

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
 SerialUSB.print(rtc.time.second);  //second
 SerialUSB.print (' ');
 if(rtc.time.Tmode == ANTI_MERIDIAN) SerialUSB.println("AM"); // print AM or PM
 else SerialUSB.println("PM");
 
 delay(500);
}
