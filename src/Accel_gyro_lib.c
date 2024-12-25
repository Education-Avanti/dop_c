/*****************************************************************************
* | File      	:   Accel_gyro_lib.c
* | Author      :   AVANTI TEAM
* | Function    :
* | Info        :
*----------------
* |	This version:   V0.1
* | Date        :   2024-27-11
* | Info        :
******************************************************************************/
#include "../include/Accel_gyro_lib.h"

/*Массив пинов светодиодов*/
int fd_1 = 0;

/*Функция инициализации датчика акселерометра и гироскопа*/
void init_accel_gyro()
{
    fd_1 = wiringPiI2CSetup(Device_Address);
	wiringPiI2CWriteReg8 (fd_1, SMPLRT_DIV, 0x07);
	wiringPiI2CWriteReg8 (fd_1, PWR_MGMT_1, 0x01);
	wiringPiI2CWriteReg8 (fd_1, CONFIG, 0);	
	wiringPiI2CWriteReg8 (fd_1, GYRO_CONFIG, 24);
	wiringPiI2CWriteReg8 (fd_1, INT_ENABLE, 0x01);
}

/*Функция измененич состояния акселерометра по оси х*/
short get_accel_x()
{
    short high_byte,low_byte,value;
	high_byte = wiringPiI2CReadReg8(fd_1, ACCEL_XOUT_H);
	low_byte = wiringPiI2CReadReg8(fd_1, ACCEL_XOUT_H + 1);
	value = (high_byte << 8) | low_byte;
	return (value/16384.0);
}
/*Функция измененич состояния акселерометра по оси у*/
short get_accel_y()
{
    short high_byte,low_byte,value;
	high_byte = wiringPiI2CReadReg8(fd_1, ACCEL_YOUT_H);
	low_byte = wiringPiI2CReadReg8(fd_1, ACCEL_YOUT_H + 1);
	value = (high_byte << 8) | low_byte;
	return (value/16384.0);
}
/*Функция измененич состояния акселерометра по оси z*/
short get_accel_z()
{
    short high_byte,low_byte,value;
	high_byte = wiringPiI2CReadReg8(fd_1, ACCEL_ZOUT_H);
	low_byte = wiringPiI2CReadReg8(fd_1, ACCEL_ZOUT_H + 1);
	value = (high_byte << 8) | low_byte;
	return (value/16384.0);
}
/*Функция измененич состояния гироскопа по оси х*/
short get_gyro_x()
{
    short high_byte,low_byte,value;
	high_byte = wiringPiI2CReadReg8(fd_1, GYRO_XOUT_H);
	low_byte = wiringPiI2CReadReg8(fd_1, GYRO_XOUT_H + 1);
	value = (high_byte << 8) | low_byte;
	return (value/131.0);
}
/*Функция измененич состояния гироскопа по оси у*/
short get_gyro_y()
{
    short high_byte,low_byte,value;
	high_byte = wiringPiI2CReadReg8(fd_1, GYRO_YOUT_H);
	low_byte = wiringPiI2CReadReg8(fd_1, GYRO_YOUT_H + 1);
	value = (high_byte << 8) | low_byte;
	return (value/131.0);
}
/*Функция измененич состояния гироскопа по оси z*/
short get_gyro_z()
{
    short high_byte,low_byte,value;
	high_byte = wiringPiI2CReadReg8(fd_1, GYRO_ZOUT_H);
	low_byte = wiringPiI2CReadReg8(fd_1, GYRO_ZOUT_H + 1);
	value = (high_byte << 8) | low_byte;
	return (value/131.0);
}