/*****************************************************************************
* | File      	:   Relay_lib.c
* | Author      :   AVANTI TEAM
* | Function    :
* | Info        :
*----------------
* |	This version:   V0.1
* | Date        :   2024-27-11
* | Info        :
******************************************************************************/
#include "../include/Relay_lib.h"

int RELAY[3] = {0, RELAY_1, RELAY_2};

/*Инициализация реле*/
void init_relay(int num)
{
if (num >= 1 && num <= 2)
    {
        pinMode(RELAY[num], OUTPUT);
        digitalWrite(RELAY[num], 0);
    }
    else
    {
        printf(RED"Check the RELAY device number!"END);
    }
}

/*Функция изменения состояния реле*/
void push_relay(int num, int mode)
{
    if ((num >= 1 && num <= 2) && (mode == 0 || mode == 1))
    {
        digitalWrite(RELAY[num], mode);
    }
    else
    {
        if (num < 1 || num > 2)
            printf(RED"Check the RELAY device number!"END);
        if (mode < 0 || mode > 1)
            printf(RED"The mod value can be 0 or 1"END);
    }
}