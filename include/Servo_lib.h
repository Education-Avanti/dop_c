/*****************************************************************************
* | File      	:   Servo_lib.h
* | Author      :   AVANTI TEAM
* | Function    :
* | Info        :
*----------------
* |	This version:   V0.1
* | Date        :   2024-27-11
* | Info        :
******************************************************************************/
#ifndef	SERVO_LIB
#define	SERVO_LIB

#include "Config.h"

/**
* GPIO_WIRINGPI 
**/
#define SERVOMOTOR      1
#define MAXPWMRANGE     2000
/*-----------------------------------------------------------------------------*/
void init_servomotor();
void get_servomotor(int angle);

#endif //SERVO_LIB