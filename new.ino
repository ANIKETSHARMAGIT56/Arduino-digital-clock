#include <Arduino.h>
// install arduino ide and install the rtclib from library manager
#include "RTClib.h"
// I AM USING DIRECT PORT MANIPULATION TO SAVE SPACE IN THE MCU BECAUSE WE ONLY HAVE 8KB FLASH IN THE ATMEGA8 CHIP
// ^^^^RTCLIB IS A LIBRARY WHICH IS USED TO TALK TO THE RTC BOARD
RTC_DS1307 rtc;
// ^^^^TELL THE LIBRARY THE NAME OF THE RTC CHIP WE WILL USE
int hourgo(int timer)
{
    int ret;
    if (timer >= 13)
    {
        ret=timer - 12;
    }
    else
    {
        ret = timer;
    }
    return ret;
}
void display(int number)
{
    //the argument with variable name "number" displays a number
    if (number == 0)
    {
        PORTD |= 63;
    }
    if (number == 1)
    {
        PORTD |= 6;
    }
    if (number == 2)
    {
        PORTD |= 91;
    }
    if (number == 3)
    {
        PORTD |= 79;
    }
    if (number == 4)
    {
        PORTD |= 102;
    }
    if (number == 5)
    {
        PORTD |= 109;
    }
    if (number == 6)
    {
        PORTD |= 125;
    }
    if (number == 7)
    {
        PORTD |= 7;
    }
    if (number == 8)
    {
        PORTD |= 127;
    }
    if (number == 9)
    {
        PORTD |= 103;
    }
}

void setup()
{
    pinMode(A1, OUTPUT);
    DDRD = 255;
    DDRB |= 3;
    if (rtc.isrunning())
    {
        // UNCOMMENT THE BELOW LINE TO SET TIME
//        rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
        // ^^^^WHAT THIS LINE BASICALLY DOES IS THAT IT STORES
        // THE TIME WHEN THE CODE WAS COMPILED
        // AND SETS IT TO THE RTC CHIP
        // this line sets the time every timewhen the code runs
        // so i advice you to upload this code to set time once
        // and comment this line
        // and upload once more
        // othervise whenever you start your clock it will be stuck to the time when the code was last compiled
    }
}
 int pug;
 int puc;
void loop()
{
    DateTime now = rtc.now();
    pug=hourgo(now.hour());
    puc=now.minute();
    int p = puc;
    int tens = p / 10;
    int ones = p - tens * 10;
    digitalWrite(8, 0);
    digitalWrite(7, 0);
    digitalWrite(9, 1);
    display(ones);
    delay(5);
    PORTD = 0;
    digitalWrite(7, 1);
    digitalWrite(8, 0);
    digitalWrite(9, 0);
    display(tens);

    delay(5);
    PORTD = 0;
    if(pug>=10){
    digitalWrite(7, 0);
    digitalWrite(8, 1);
    digitalWrite(9, 0);
    digitalWrite(A1,1);
    int pun=pug-10;
    display(pun);
    delay(5);
    PORTD = 0;
    }
    
    if(pug<=9){
    digitalWrite(7, 0);
    digitalWrite(8, 1);
    digitalWrite(9, 0);
    digitalWrite(A1,0);
    display(pug);
    delay(5);
    PORTD = 0;
    }
}
