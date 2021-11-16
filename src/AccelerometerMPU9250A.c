#include <wiringPi.h>
#include <wiringPiI2C.h>
#include <inttypes.h>
#include "AccelerometerMPU9250A.h"

int fd;


int MPU9520A_read(int Reg_adress)
{
    return wiringPiI2CReadReg8(fd, Reg_adress);
}
void MPU9520A_write(int Reg_adress, int Data)
{
    wiringPiI2CWriteReg8(fd, Reg_adress, Data);
}


void MPU9520A_Init()
{
    fd = wiringPiI2CSetup(AccelerometrID);
    if(fd)
    {
        MPU9520A_set_G_parameter(ACCEL_FS_SEL_2G);
    }
    else
    {
        printf("error");
    }
}

void MPU9520A_set_G_parameter(int g_param)
{
    __uint8_t x;
    x = MPU9520A_read(ACCEL_CONFIG);
    x = (ACCEL_FS_MASK & x);
    MPU9520A_write(ACCEL_CONFIG, (g_param | x));

}

int MPU9520A_READ_AXIS(int Axie)
{
    int16_t g =0;
    switch (Axie)
    {
    case AXIE_X:
        g = MPU9520A_read(ACCEL_XOUT_H);
        break;
    case AXIE_Y:
        g = MPU9520A_read(ACCEL_YOUT_H);
        break;
    case AXIE_Z:
        g = MPU9520A_read(ACCEL_ZOUT_H);
        break;
    default:
        break;
    }
    g = g <<8;
    return g;
}


float MPU9520A_READ_AXIS_IN_G(int Axie)
{
    uint8_t x =0;
    float acceleration = MPU9520A_READ_AXIS(Axie);
    float g = 0;
    x = MPU9520A_read(ACCEL_CONFIG);
    x = (~ACCEL_FS_MASK & x);
    float divisor = 1;
    switch (x)
    {
    case ACCEL_FS_SEL_2G:
        divisor = 16384;
        break;
    case ACCEL_FS_SEL_4G:
        divisor = 8192;
        break;
    case ACCEL_FS_SEL_8G:
        divisor = 4096;
        break;
    case ACCEL_FS_SEL_16G:
         divisor = 2048;
        break;
    default:
        break;
    }
    g = acceleration/divisor;
    return g;
}