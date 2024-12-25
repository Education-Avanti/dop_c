/*****************************************************************************
* | File      	:   Joystick_lib.h
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
#ifndef	JOYSTICK_LIB
#define	JOYSTICK_LIB

#include "Config.h"

#define JOYSTICK_ADDR   0x48
#define JOYSTICK_1      26
#define JOYSTICK_X      0x40
#define JOYSTICK_Y      0x41

void init_joystick();

int get_axis_y();

int get_axis_x();

int get_axis_button();

#endif //JOYSTICK_LIB