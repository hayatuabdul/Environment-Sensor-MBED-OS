#include "mbed.h"
#include "stdio.h"
#include "FATFileSystem.h"
#include <BufferedSerial.h>
#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <ratio>
#include <string.h>
#include <string>

BufferedSerial pc(PD_8, PD_9,9600);
//Thread for communication with serial interface
char serial_input[32];

char mode[30];
char part1[30];
char part2[30];

float period;

char ascii_enter = '\r';
char ascii_space = ' ';

int i = 0;
int j = 0;
int k = 0;
int l = 0;

int buff = 0;

extern double n,n1,n2;
string temp, press, ll;

void Serial_Menu()
{
    pc.write("SERIAL PROTOCOL\n\n\r",19);
    pc.write("READNOW    ..............Reads current record\n\r",48);
    pc.write("READBUFFER \"N\"...........Reads \"N\" number of records\n\r",55);
    pc.write("CHARTMODE  \"T|H|P|L\".....Specify the parameter to be plotted on bar chart\n\r",75);
    pc.write("BARMODE    \"T|H|P|L\".....Specify the parameter to be plotted on LED matrix\n\r",76);
    pc.write("SET        \"T\"...........Set sampling period to \"T\"\n\r",54);
    pc.write("STATE      \"ON|OFF\"......Turn sampling on or off\n\r",50);
    pc.write("LOGGING    \"ON|OFF\"......Diagnostic logging to serial interface\n\r",66);
    pc.write("SD         \"F|E\".........SD card Flush or Eject\n\n\r",51);
}

void clear_buffer()
{
    for (buff = 0; buff < 30; buff ++)
    {
        mode[buff] = '\0';
        part1[buff] = '\0';
        part2[buff] = '\0';
    }
    i = 0;
    j = 0;
    k = 0;
    l = 0;
}

void select_parameter()
{
    if (part2 == string("T"))
    {
        pc.write("you have selected Temperature\n\r",31);
    }
    else if (part2 == string("H"))
    {
        pc.write("you have selected Humidity\n\r",29);
    }
    else if (part2 == string("P"))
    {
        pc.write("you have selected Pressure\n\r",29);
    }
    else if (part2 == string("L"))
    {
        pc.write("you have selected Light Levels\n\r",33);
    }
    else 
    {
        pc.write("incorrect parameter, try again\n\r",33);
    }
}

void select_samp_period()
{
    period = atof(part2);
    if (period >= 0.1 && period <= 30)
    {
        pc.write("you have selected period\n\r",31);
    }
    else 
    {
        pc.write("out of range, try again\n\r",25);
    }
}

void select_sd_mode()
{
    if (part2 == string("E"))
    {
        pc.write("you have selected Eject\n\r",25);
    }
    else if (part2 == string("F"))
    {
        pc.write("you have selected Flush\n\r",25);
    }
    else 
    {
        pc.write("incorrect option, try again\n\r",29);
    }
}

void select_on_off()
{
    if (part2 == string("ON"))
    {
        pc.write("you have selected on\n\r",22);
    }
    else if (part2 == string("OFF"))
    {
        pc.write("you have selected off\n\r",23);
    }
    else 
    {
        pc.write("incorrect choice, try again\n\r",29);
    }
}

void Serial_Read()
{
	//Print Protocol menu using printf 
	Serial_Menu();

    while(1)
    {
        pc.read(serial_input,sizeof(serial_input));
        if (serial_input[0] == ascii_enter)
        {
            for (j = 0; j < 30; j ++)                   //iterate through all elements of the input array
            {
                if (mode[j] == ascii_space)             //if the string contains a space
                { 
                    for (k = 0; k < j; k++)             //everything before it becomes part 1
                    {
                        part1[k] = mode[k];             //copy all characters prior to the space
                    }
                    
                    for (l = 0; j < 30; l++)
                    {
                        part2[l] = mode[j+1];               //everything after it becomes part 2
                        j++;
                    }
                }

            }
            
            pc.write("\n\rCOMMAND: ",11);
            pc.write(part1,sizeof(part1));

            if (mode == string("READNOW"))
            {
                pc.write("\n\rread now has been selected\n\r",30);
                
                pc.write((&n),sizeof(n));
                pc.write((&n1),sizeof(n1));
                pc.write((&n2),sizeof(n2));                
                clear_buffer();
            }
            else if (part1 == string("READBUFFER"))
            {
                pc.write("\n\rread buffer has been selected\n\r",33);
                pc.write("you have selected ",18);
                pc.write(part2,sizeof(part2));
                pc.write(" records\n\r",10);
                clear_buffer();
            }
            else if (part1 == string("CHARTMODE"))
            {
                pc.write("\n\rchart mode has been selected\n\r",32);
                select_parameter();
                clear_buffer();
            }
            else if (part1 == string("BARMODE"))
            {
                pc.write("\n\rbar mode has been selected\n\r",30);
                select_parameter();
                clear_buffer();
            }
            else if (part1 == string("SET"))
            {
                pc.write("\n\rsampling period has been selected\n\r",37);
                select_samp_period();
                clear_buffer();
            }
            else if (part1 == string("STATE"))
            {
                pc.write("\n\rsampling on or off selected\n\r",31);
                select_on_off();
                clear_buffer();
            }
            else if (part1 == string("LOGGING"))
            {
                pc.write("\n\rlogging on or off has been selected\n\r",39);
                select_on_off();
                clear_buffer();
            }
            else if (part1 == string("SD"))
            {
                pc.write("\n\rSD has been selected\n\r",24);
                select_sd_mode();
                clear_buffer();
            }
            else 
            {
                pc.write("\n\rUnknown command, please try again\n\r",37);
                clear_buffer();
            }
        }
        else
        {
            mode[i] = serial_input[0];
            i++;
        }
    }
}

