/*****************************************************************************
* | File      	:   Obstacle_lib.h
* | Author      :   AVANTI TEAM
* | Function    :
* | Info        :
*----------------
* |	This version:   V0.1
* | Date        :   2024-27-11
* | Info        :
******************************************************************************/
#ifndef	OBSTACLE_LIB
#define	OBSTACLE_LIB

#include "Config.h"

/**
* GPIO_WIRINGPI 
**/
#define OBSTACLE_SENSOR 6
/*-----------------------------------------------------------------------------*/
void init_obstacle_sensor();
int get_obstacle_sensor();

#endif //OBSTACLE_LIB