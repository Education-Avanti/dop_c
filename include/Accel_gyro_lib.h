/*****************************************************************************
* | File      	:   Accel_gyro_lib.h
* | Author      :   AVANTI TEAM
* | Function    :
* | Info        :
*----------------
* |	This version:   V0.1
* | Date        :   2024-27-11
* | Info        :
******************************************************************************/
#ifndef	ACCEL_GYRO_LIB
#define	ACCEL_GYRO_LIB

#include "Config.h"

/**
* GPIO_WIRINGPI 
**/
#define Device_Address  0x68

#define PWR_MGMT_1      0x6B
#define SMPLRT_DIV      0x19
#define CONFIG          0x1A
#define GYRO_CONFIG     0x1B
#define INT_ENABLE      0x38
#define ACCEL_XOUT_H    0x3B
#define ACCEL_YOUT_H    0x3D
#define ACCEL_ZOUT_H    0x3F
#define GYRO_XOUT_H     0x43
#define GYRO_YOUT_H     0x45
#define GYRO_ZOUT_H     0x47
/*-----------------------------------------------------------------------------*/
void init_accel_gyro();
short get_gyro_x();
short get_gyro_y();
short get_gyro_z();
short get_accel_x();
short get_accel_y();
short get_accel_z();

#endif //ACCEL_GYRO_LIB