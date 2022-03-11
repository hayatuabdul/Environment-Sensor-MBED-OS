#ifndef __RINGBUFFER__
#define __RINGBUFFER__

#include "mbed.h"
//#include "F429_Mega_Shell_Header.h"

#define BufferSize 10


class RingBuffer 
{
private:

    //Buffer Data Length
    double Buffer[BufferSize][3];
    int tail;   //same as tail
    int head;  //same as head
    Mutex mutex;
 
public:

    bool full();
    bool empty();
    void push(double x, double y, double z);     
    double pop();
    //int write_sdcard();
    RingBuffer()
    {
        tail = -1;
        head = -1;
    }
   
};

#endif