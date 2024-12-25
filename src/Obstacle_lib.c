/*****************************************************************************
* | File      	:   Obstacle_lib.c
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
#include "../include/Obstacle_lib.h"

/*Инициализация датчика препятствия*/
void init_obstacle_sensor()
{
    pinMode(OBSTACLE_SENSOR, INPUT);
}

/*Функция получения сигнала с датчика*/
int get_obstacle_sensor()
{
    return(!digitalRead(OBSTACLE_SENSOR));
}