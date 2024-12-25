/*****************************************************************************
* | File      	:   Config.h
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
#ifndef	CONFIG_H
#define	CONFIG_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <fcntl.h>
#include <termio.h>
#include <termios.h>
#include <signal.h>
#include <string.h>
#include <regex.h>
#include <dirent.h>
#include <errno.h>
#include <stdint.h>
#include <math.h>
#include <softPwm.h>

#include <wiringPi.h>
#include <wiringPiI2C.h>

/**
 * Директива состояния
**/
#define LOW             0
#define HIGH            1

/**
 * Color text
**/
#define RED             "\033[31m"
#define GRE             "\033[32m"
#define YEL             "\033[33m"
#define BLU             "\033[34m"
#define MAG             "\033[35m"
#define END             "\033[0m"
/*-----------------------------------------------------------------------------*/
void init_lib(void);

#endif //CONFIG