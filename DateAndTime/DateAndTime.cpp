#include "DateAndTime.h"
#include "mbed.h"

#define SAMPLES 300

// SWITCHES A B C D.  NB C and D are configured for open drain inputs need a pull down as when switch is not pressed then has a floating input
DigitalIn swA(PG_0);
DigitalIn swB(PG_1);
DigitalInOut swC(PG_2,PIN_INPUT,OpenDrainPullDown,0);
DigitalInOut swD(PG_3,PIN_INPUT,OpenDrainPullDown,0);

//Analogue Inputs
AnalogIn pot_an_input(PA_0);

//Initialise Timer for switches
Timer switch_timer;

//Call variable initialised in main
extern int digit_select;
extern int Day, Month, Year_1, Year_2, Hour, Minutes;

int  DateAndTime::DigitSelect(){
    
    // Variable Name for the switch
    char switchNum=' '; 
    // Set name to switch variable
    if (swA)switchNum='A';
    if (swB)switchNum='B';
    if (swC)switchNum='C';
    if (swD)switchNum='D';

    switch_timer.start();

    switch(switchNum){ 
        //A digit is each variable: Digit one: day, digit two: month...
        case 'A':  // if switch A is pressed -> select last digit.
            while (switch_timer.elapsed_time() < 500ms); // If the switch is not blocked, it could detect the input more times that the ones desired 
            digit_select = 6;
        break;   
                    
        case 'B': // if switch B is pressed -> select the digit on the left.
            while (switch_timer.elapsed_time() < 500ms);
            digit_select = digit_select -1;
        break; 
        
        case 'C': // if switch C is pressed -> select first digit.
            while (switch_timer.elapsed_time() < 500ms);
            digit_select = 0;
        break;
                
        case 'D': // if switch D is pressed -> select next digit.  
            while (switch_timer.elapsed_time() < 500ms);
            digit_select = digit_select +1;
        break; 
        
        default:// Default settings if no switchs are pressed.
            switchNum=' ';
            digit_select=digit_select;
        break;
    }
    //Reset and stop the timer used.
    switch_timer.reset(); 
    switch_timer.stop();

    //There is only 5 digits that we can change 
    if (digit_select>6){ digit_select =6;} //If the digit value is bigger than 5, the variable will be reset to 5
    if (digit_select<1){ digit_select = 1;}//If the digit value is smaller than 1, the variable will be reset to 1

    return digit_select;
}
void  DateAndTime::UpdateClock(){
    // Potentiometer should be used to set a value
    int measured_potav_day = (32*(int)potav())/100;
    int measured_potav_month = (13*(int)potav())/100;
    //To archieve more stability in the year, the year will be controlled in groups of two
    int measured_potav_year_1 = (int)(potav());//First two digits 
    int measured_potav_year_2 = (int)(potav());//Last two digits of the year

    int measured_potav_hour = (24*(int)potav())/100;
    int measured_potav_min = (60*(int)potav())/100;

    switch(digit_select){ 
        case 1: Day = measured_potav_day;       break;       
        case 2: Month = measured_potav_month;   break; 
        case 3: Year_1 = measured_potav_year_1; break;  
        case 4: Year_2 = measured_potav_year_1; break;
        case 5: Hour = measured_potav_hour;     break; 
        case 6: Minutes = measured_potav_min;   break;
    } 
}

float DateAndTime::potav(){
    unsigned int adc_sample[SAMPLES+1];
    adc_sample[0]=0;
    for(int i=1; i<=SAMPLES; i++){
        adc_sample[i] = pot_an_input.read_u16();
        adc_sample[0]+=adc_sample[i];
    }
    float ADC_Conversion = 100 * ((float)adc_sample[0]/(float)SAMPLES)/65535.0f;
    return ADC_Conversion;
}