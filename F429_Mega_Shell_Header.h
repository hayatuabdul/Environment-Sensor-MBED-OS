#ifndef F429_MEGA_SHELL_HEADER_H
#define F429_MEGA_SHELL_HEADER_H

#include "mbed.h"
//#include "TextLCD.h"
//#include "BMP280_SPI.h"

// Blinking rate in milliseconds
#define BLINKING_RATE_MS     500ms
//IDE Constants
#define DELAY 2000ms
#define RED   1
#define AMBER 2
#define GREEN 4

#define rgb 0   //no Latch
#define Rgb 1   //Red Latch
#define rGb 2   //Green Latch
#define rgB 4   //Blue Latch

#define SCAN_RATE_MS   50

// 7 Segment labels A to G and Decimal Point (DP)
#define A  0x10
#define B  0x20
#define C  0x40
#define D  0x08
#define E  0x02
#define F  0x01
#define G  0x04
#define DP 0x80

#define WAIT_TIME_MS 1000

//API Class type instance

// LCD
#include "TextLCD.h"
TextLCD myLCD(PD_11, PD_13, PD_12, PD_4,PD_5,PD_6,PD_7);   // rs, e, rw,  then data lines =  d4,d5,d6,d7
PwmOut myLCD_BL(PD_14);

// SOUNDER
PwmOut buzzer(PB_13);

// TRAFFIC LIGHTS (NON LATCHED LEDS)
BusOut Traffic_Lights_1(PC_2,PC_3,PC_6);                //BusOut here can be DigitalOut
BusInOut Traffic_Lights_2(PC_7,PC_8,PC_9);              //NB this is BusInOut for open drain  you will need to add the following lines
                                                        // Traffic_Lights_2.output();
                                                        // Traffic_Lights_2.mode(OpenDrainNoPull);
                                                        // Traffic_Lights_2=assign a value remember that 1==OFF and 0==ON
                                                        //however..
                                                        //can use DigitalInOut see 'Pedestrian' for example
DigitalInOut Pedestrian(PF_10,PIN_OUTPUT,OpenDrain,1);  //Set as output, open drain, and set high to switch LED off initially 1==OFF 0==ON

// RGB Bar LED LATCHED by used of RGBcol, number of LEDS selected by RGBled, output enable active LOW
BusOut RGBled(PE_2, PE_3, PE_4, PE_5, PE_6, PE_7, PE_8, PE_9);
BusOut RGBcol(PE_12, PE_13, PE_14);
DigitalOut RGBoe(PE_0,1);

//Analogue Inputs
AnalogIn microphone(PA_3);
AnalogIn signal_in(PA_6);
AnalogIn audio_in_L(PB_0);
AnalogIn audio_in_R(PB_1);

//Analogue Outputs
AnalogOut dac_out_1(PA_4);
AnalogOut dac_out_2(PA_5);

// MATRIX DISPLAY SPI WITH OUTPUT ENABLE
SPI spi(PC_12, PC_11, PC_10);   // MOSI, MISO, SCLK
DigitalOut cs(PB_6);            //Chip Select ACTIVE LOW
DigitalOut oe(PB_12);           //Output Enable ACTIVE LOW

// 7 SEGMENT DISPLAY LATCHED AND OUTPUT ENABLED
BusOut seg7(PE_2, PE_3, PE_4, PE_5, PE_6, PE_7, PE_8, PE_9);
DigitalOut LatE1(PE_10,0);
DigitalOut LatE2(PE_11,0);
DigitalOut nOE(PE_15,0);


#endif