/*****************************************************************************
* | File      	:   Led_lib.h
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
#ifndef	LED_LIB
#define	LED_LIB

#include "Config.h"

/**
* GPIO_WIRINGPI 
**/
#define LED_1           0
#define LED_2           2
#define LED_3           3
/*-----------------------------------------------------------------------------*/
void init_led(int num);
void light_led(int num, int mode);

#endif //LED_LIB