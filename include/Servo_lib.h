/*****************************************************************************
* | File      	:   Servo_lib.h
* | Author      :   AVANTI TEAM
* | Function    :   ПОКА НЕ ПРИДУМАЛ
* | Info        :
*                Надо
*                подумать
*----------------
* |	This version:   V0.1
* | Date        :   2024-27-11
* | Info        :

#
#
#
#
#
#
#                   НАПИСАТЬ ЧТО_ТО УМНОЕ
#
#
#
#
#
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