/*****************************************************************************
* | File      	:   Color_module_lib.c
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

#include "../include/Color_module_lib.h"

struct termios tty;
UWORD r,g,b,c;
UWORD cpl,lux,k;
RGB rgb;
UDOUBLE RGB888 = 0;
UWORD   RGB565 = 0;

void init_color_module()
{
    if (DEV_ModuleInit() != 0)
    {
        exit(0);
    }
    if(TCS34725_Init() != 0)
    {
        exit(0);
    } 
}

int get_color_red_RGB888()
{
    UDOUBLE RGB888=0;
    rgb=TCS34725_Get_RGBData();
    RGB888=TCS34725_GetRGB888(rgb);
    return(RGB888>>16);
}

int get_color_green_RGB888()
{
    rgb=TCS34725_Get_RGBData();
    RGB888=TCS34725_GetRGB888(rgb);
    return((RGB888>>8) & 0xff);
}

int get_color_blue_RGB888()
{
    rgb=TCS34725_Get_RGBData();
    RGB888=TCS34725_GetRGB888(rgb);
    return((RGB888) & 0xff);
}

int get_color_RGB888()
{
    rgb=TCS34725_Get_RGBData();
    return(TCS34725_GetRGB888(rgb));
}

int get_color_RGB565()
{
    rgb=TCS34725_Get_RGBData();
    return(TCS34725_GetRGB565(rgb));
}

int get_color_RGBData()
{
    rgb=TCS34725_Get_RGBData();
    return(rgb.C); 
}