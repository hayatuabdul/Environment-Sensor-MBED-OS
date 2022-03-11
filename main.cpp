/*//////////////////////////////////////////////////////////////////////////////////
Students: Laura Alvarez Hidalgo
          Hayatu 
          Mauricio Cordoba Andrews

Year: 2020 - 2021
*//////////////////////////////////////////////////////////////////////////////////
#include "mbed.h"
#include "F429_Mega_Shell_Header.h"
//#include "TextLCD/TextLCD.h"
/*
#include <cstdio>
#include <iostream>
*/
#include "Measurements.h"
#include "RingBuffer.h"
#include "html.h"
#include "DateAndTime.h"
#include "serial.h"

//Initialising the constructor
Measurements Sensordata;
DateAndTime Calendar;

double n,n1,n2;//n(BufferTemperature)|n2(BufferPressure)|n3(BufferLightLevel)
int digit_select = 0;
int Day=0, Month=0, Year_1=0, Year_2=0, Hour=0, Minutes=0;
void Producer ();

//Threads
Thread T1; //Buffer 
Thread T2;
Thread T3;

int main (){    
    //Reset state of the LCD
    myLCD.cls();

    T1.start(Producer);
    T2.start(Network_Respond);
    T3.start(Serial_Read);

    while (true){
        Calendar.DigitSelect();
        Calendar.UpdateClock();

        myLCD.locate(0,0);//To Write in the first line 
        myLCD.printf("DATE: %d/%d/%d%d",Day,Month,Year_1,Year_2);
        myLCD.locate(0,1);//To Write in the second line 
        myLCD.printf("TIME: %d:%d",Hour,Minutes);
        sleep();
    }
}

void Producer (void)
{
    RingBuffer q;
    while(true)
    {
        q.push(Sensordata.Temperature(), Sensordata.Pressure(), Sensordata.LightLevel());
        q.push(Sensordata.Temperature(), Sensordata.Pressure(), Sensordata.LightLevel());
        q.pop();
        //q.pop();
        thread_sleep_for(20000); 
    }
}