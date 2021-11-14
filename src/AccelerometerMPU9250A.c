#include <wiringPi.h>
#include <wiringPiI2C.h>
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
        MPU9520A_set_G_parameter(ACCEL_FS_SEL_4G);
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