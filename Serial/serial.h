#ifndef __SERIAL__
#define __SERIAL__

#include "mbed.h"

extern void Serial_Read();
extern void Serial_Menu();
extern void clear_buffer();
extern void select_parameter();
extern void select_samp_period();
extern void select_sd_mode();
extern void select_on_off();
#endif