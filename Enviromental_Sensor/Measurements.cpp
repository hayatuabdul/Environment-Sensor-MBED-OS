#include "Measurements.h"
#include "mbed.h"

#define Dew_Temperature 18.3

#include "BMP280_SPI.h"
BMP280_SPI bmp280(PB_5, PB_4, PB_3, PB_2);

AnalogIn ldr(PC_0);

double Measurements::Temperature(){
    double T = bmp280.getTemperature();
    return T;
}

double Measurements::Pressure(){
    double P = bmp280.getPressure();
    return P;
}

double Measurements::Humidity(){
    double Satured_Vapour_Pressure = 6.11*exp(((17.67*Temperature())/(243.5+Temperature())));
    double Vapor_Pressure = 6.11*exp(((17.67*Dew_Temperature)/(243.5+Dew_Temperature)));
    double H = (Vapor_Pressure/Satured_Vapour_Pressure)*100; //Calculate Humidity
    return H;
}

int Measurements::LightLevel(){
    float LDR_Values = ldr.read();
    int L = (int)(LDR_Values*10);
    return L;
}