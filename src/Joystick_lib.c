/*****************************************************************************
* | File      	:   Joystick_lib.c
* | Author      :   AVANTI TEAM
* | Function    :
* | Info        :
*----------------
* |	This version:   V0.1
* | Date        :   2024-27-11
* | Info        :
******************************************************************************/
#include "../include/Joystick_lib.h"

int fd_3 = 0;

/*Инициализации джостика*/
void init_joystick()
{
    fd_3 = wiringPiI2CSetup(JOYSTICK_ADDR);
    if (fd_3 == -1)
    {
        printf("Ошибка подключения к PCF8591\n");
    }
    pinMode(JOYSTICK_1, INPUT);
}

/*Получение значений оси У*/
int get_axis_y()
{
    wiringPiI2CWrite(fd_3, JOYSTICK_Y);
    usleep(1000);
    wiringPiI2CRead(fd_3);
    usleep(1000);
    return wiringPiI2CRead(fd_3);  
}

/*Получение значений оси У*/
int get_axis_x()
{
    wiringPiI2CWrite(fd_3, JOYSTICK_X);
    usleep(1000);
    wiringPiI2CRead(fd_3);
    usleep(1000);
    return(wiringPiI2CRead(fd_3));  
}

/*Функция получения состояния кнопки джойстика*/
int get_axis_button()
{
    return(!digitalRead(JOYSTICK_1));
}