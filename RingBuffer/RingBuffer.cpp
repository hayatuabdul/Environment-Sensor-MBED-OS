#include "mbed.h"
#include "RingBuffer.h"
#include <iostream>
//#include "F429_Mega_Shell_Header.h"
#include "SDBlockDevice.h"
#include "FATFileSystem.h"
DigitalOut led1(LED1);
DigitalOut led2(LED2);
DigitalOut led3(LED3);
// Instantiate the SDBlockDevice by specifying the SPI pins connected to the SDCard
// socket. The PINS are: (This can also be done in the JSON file see mbed.org Docs API Storage SDBlockDevice)
// PB_5    MOSI (Master Out Slave In)
// PB_4    MISO (Master In Slave Out)
// PB_3    SCLK (Serial Clock)
// PF_3    CS (Chip Select)
//
// and there is a Card Detect CD on PF_4 ! (NB this is an Interrupt capable pin..)
SDBlockDevice sd(PB_5, PB_4, PB_3, PF_3);

extern double n;
extern double n1;
extern double n2;

bool RingBuffer :: full()
{
   if (head == (tail + 1) % BufferSize)
     {
        return true;
     }
     else
        return false;
}

bool RingBuffer :: empty()
{
   
     if (head == tail)
     {
        return true;
     }
     else
        return false;
}


void RingBuffer :: push(double x, double y, double z)
{
    
    if(full())
    {
        cout << "Buffer is full\n";
       //led1 = 1;
        //led2 = 1;
        // Light red led when buffer becomes full
        led3 = 1;
    } 
     
    else 
    {

        mutex.lock();
        tail = (tail + 1) % BufferSize;   // Go around the circular buffer
        
        // Inserts element
        Buffer[tail][0] = x;
        Buffer[tail][1] = y;
        Buffer[tail][2] = z;
        mutex.unlock();

       // Start reading Buffer
        if(head == -1)
        {   
            head = 0;
        }
    
        //cout << endl << "Inserted " << x << endl;
    }
}

double RingBuffer :: pop()
{

    
    if(empty())
    {
        cout << "Buffer is empty\n" << endl;
    } 
    else 
    {
        mutex.lock();
        // Read and remove element
        n =  Buffer[head][0];
        n1 = Buffer[head][1];
        n2 = Buffer[head][2];

        //Uncomment next lines for testing
        /*
        cout << n << endl;
        cout << n1 << endl;
        cout << n2 << endl;
        */

        //FILE *fp = fopen("/sd/SDCardData.txt","w");
        //fprintf(fp, "Temperature = %.2f DegC\nPressure = %.2f mbar\nLight Levels = %f\n\n",n,n,n);

        if(head == tail)
        {
            // Reset queue after cycle
            head = -1;
            tail = -1;
        }
        else 
        {
            head = (head+1) % BufferSize;   // Increment head/Head reads around circular buffer
        }
        mutex.unlock();


         printf("Initialise and write to a file\n");
    // call the SDBlockDevice instance initialisation method.
    if ( 0 != sd.init()) {
        printf("Init failed \n");
        
        return -1;
    }
    FATFileSystem fs("sd", &sd);
         led2 = 1;
         thread_sleep_for(2000);
         led2 = 0;
    FILE *fp = fopen("/sd/SDCardDataLau.txt","w");
    if(fp == NULL) {
        error("Could not open file for write\n");
        sd.deinit();
        return -1;
    } else {
       
        //Put some text in the file...
        //fprintf(fp, q.push(2));
        
        fprintf(fp, "Temperature = %.2f DegC\nPressure = %.2f mbar\nLight Levels = %f\n\n",n,n1,n2);
        
       
        //Tidy up here
        fclose(fp);
        printf("SD Write done...\n");
        
        sd.deinit();
        return 0;
    
    
}
        
    }
      

        
    return(n);
     
}


