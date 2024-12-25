/*****************************************************************************
* | File      	:   Button_lib.h
* | Author      :   AVANTI TEAM
* | Function    :
* | Info        :
*----------------
* |	This version:   V0.1
* | Date        :   2024-27-11
* | Info        :
******************************************************************************/
#ifndef	BUTTON_LIB
#define	BUTTON_LIB

#include "Config.h"

/**
* GPIO_WIRINGPI 
**/
#define BUTTON_1        21
#define BUTTON_2        22
#define BUTTON_3        25
/*-----------------------------------------------------------------------------*/
void init_button(unsigned int num);

int button_push(unsigned int num);
int button_hold(unsigned int num, unsigned int holding_time);

bool debounce(unsigned int num);
bool button_push_hold(unsigned int num);

#endif //BUTTON_LIB