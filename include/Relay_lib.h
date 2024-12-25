/*****************************************************************************
* | File      	:   Relay_lib.h
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
#ifndef	RELAY_LIB
#define	RELAY_LIB

#include "Config.h"

/**
* GPIO_WIRINGPI 
**/
#define RELAY_1         4
#define RELAY_2         5
/*-----------------------------------------------------------------------------*/
void init_relay(int num);
void push_relay(int num, int mode);

#endif //RELAY_LIB