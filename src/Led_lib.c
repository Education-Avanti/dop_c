/*****************************************************************************
* | File      	:   Led_lib.c
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
#include "../include/Led_lib.h"

/*Массив пинов светодиодов*/
int LED[4] = {0, LED_1, LED_2, LED_3};

/*Функция инициализации светодиодов*/
void init_led(int num)
{
    if (num >= 1 && num <= 3)
    {
        pinMode(LED[num], OUTPUT);
        digitalWrite(LED[num], LOW);
    }
    else
    {
        printf(RED"Check the LED device number!"END);
    }
}

/*Функция измененич состояния светодиодов*/
void light_led(int num, int mode)
{
    if ((num >= 1 && num <= 3) && (mode == 0 || mode == 1))
    {
        digitalWrite(LED[num], mode);
    }
    else
    {
        if (num < 1 || num > 3)
            printf(RED"Check the LED device number!"END);
        if (mode < 0 || mode > 1)
            printf(RED"The mod value can be 0 or 1"END);
    }
}