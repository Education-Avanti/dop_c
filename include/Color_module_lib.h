/*****************************************************************************
* | File      	:   Led_lib.h
* | Author      :   AVANTI TEAM
* | Function    :
* | Info        :
*----------------
* |	This version:   V0.1
* | Date        :   2024-27-11
* | Info        :
******************************************************************************/
#ifndef	COLOR_MODULE
#define	COLOR_MODULE

#include "Config.h"
#include "../include/TCS34725.h"

/**
* GPIO_WIRINGPI 
**/

/*-----------------------------------------------------------------------------*/
void init_color_module();
int get_color_red_RGB888();
int get_color_green_RGB888();
int get_color_blue_RGB888();
int get_color_RGB888();
int get_color_RGB565();
int get_color_RGBDatavoid();

#endif //COLOR_MODULE