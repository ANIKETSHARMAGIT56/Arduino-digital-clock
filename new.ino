#include <Arduino.h>
#include<SPI.h>
#include "RTClib.h"

RTC_DS1307 rtc;
const char numbers[]={
0B01111110,
0B00110000,
0B01101101,
0B01111001,
0B00110011,
0B01011011,
0B01011111,
0B01110000,
0B01111111,
0B01111011,
};

#define DPIN0 16
#define DPIN1 5
#define DPIN2 4
#define DPIN3 0
#define DPIN4 2
#define DPIN5 14
#define DPIN6 12
#define DPIN7 13
#define DPIN8 15





const byte latch_p= DPIN6;
const byte clock_p= DPIN7;
const byte data_p = DPIN8;

const byte display_place[4]={DPIN5,DPIN4,DPIN3,DPIN0};
const int SSpin = 12;


void setup() {
#ifndef ESP8266
  while (!Serial); // wait for serial port to connect. Needed for native USB
#endif
  if (! rtc.begin()) {
    Serial.println("Couldn't find RTC");
    Serial.flush();
    while (1) delay(10);
  }
  //   pinMode(SSpin, OUTPUT);
  // SPI.begin();
  	
  pinMode(latch_p, OUTPUT);
  pinMode(clock_p, OUTPUT);
  pinMode(data_p, OUTPUT);
  pinMode(display_place[0], OUTPUT);
  pinMode(display_place[1], OUTPUT);
  pinMode(display_place[2], OUTPUT);
  pinMode(display_place[3], OUTPUT);


}
int toggle_display(int number,int clear){
  if (clear==1){
    for (int i = 0; i < 4; i++)
    {
      digitalWrite(display_place[i],HIGH);
    }
    return 0;
  }
  for (int i = 0; i < 4; i++)
  {
    if (i==number)
    {
    digitalWrite(display_place[i],LOW);
      /* code */
    }
    else{
      digitalWrite(display_place[i],HIGH);
    }
    
  }
   return 0;
  
}

void display_no(int number , int display){
  toggle_display(display,1);
    digitalWrite(latch_p,0);
  shiftOut(data_p,clock_p,LSBFIRST,numbers[number]);
  digitalWrite(latch_p,1);
  toggle_display(display,0);

}
int i=5;
void display_buffer(int * buf,int del){
  display_no(*buf,3);
  delay(del);
  display_no(*(buf+1),2);
  delay(del);
  display_no(*(buf+2),1);
  delay(del);
  display_no(*(buf+3),0);
  delay(del);
}
void loop() {
  DateTime now = rtc.now();
  int buff[4]={(now.hour()-(now.hour()%10))/10,(now.hour()%10),(now.minute()-(now.minute()%10))/10,(now.minute()%10)};
display_buffer(&buff[0],5);

}



 
