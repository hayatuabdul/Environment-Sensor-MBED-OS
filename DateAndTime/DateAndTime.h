#ifndef _DATEANDTIME_H
#define _DATEANDTIME_H

class DateAndTime{
    private:
        int _Day;
        int _Month;
        int _Year1;
        int _Year2;
        int _Hour;
        int _Minutes;
    public:
    //Constructor
    DateAndTime(){int Day; int Month; int Year1; int Year2; int Hour; int Minutes;};
    // Member Functions
    int DigitSelect();
    float potav();
    void UpdateClock();
    
};

#endif