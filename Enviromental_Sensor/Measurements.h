#ifndef _MEASUREMENTS_H
#define _MEASUREMENTS_H



class Measurements{
    private:
        double _Temperature;
        double _Pressure;
        double _Humidity;
        int _LightLevel;
    public:
    //Constructor
   Measurements(){double Temperature; double Pressure; double Humidity; int LightLevel;};
    //
    double Temperature();
    double Pressure();
    double Humidity();
    int LightLevel();
    //
    

};

#endif