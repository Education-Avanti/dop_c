/*****************************************************************************
* | File      	:   Servo_lib.c
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
#include "../include/Servo_lib.h"

float minDC = 1.75;
float maxDC = 11.85;

/*Инициализации сервомотора*/
void init_servomotor()
{
    pinMode (SERVOMOTOR, PWM_OUTPUT);
    pwmSetMode(PWM_MODE_MS);   
    pwmSetClock(192);
}

/*Изменение состояния качалки по углу*/
void get_servomotor(int angle)
{
    pwmWrite (SERVOMOTOR, (angle*(maxDC-minDC)/180+minDC)/100*MAXPWMRANGE);
}