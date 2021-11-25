#include <wiringPi.h>
#include <wiringPiI2C.h>
#include <inttypes.h>
#include <math.h>
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
        MPU9520A_write(ACCEL_CONFIG_2, 0b00001110);
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
    int16_t g2 = 0;
    switch (Axie)
    {
    case AXIE_X:
        g = MPU9520A_read(ACCEL_XOUT_H);
        g2 = MPU9520A_read(ACCEL_XOUT_L);
        break;
    case AXIE_Y:
        g = MPU9520A_read(ACCEL_YOUT_H);
        g2 = MPU9520A_read(ACCEL_YOUT_L);
        break;
    case AXIE_Z:
        g = MPU9520A_read(ACCEL_ZOUT_H);
        g2 = MPU9520A_read(ACCEL_ZOUT_L);
        break;
    default:
        break;
    }
    g = g <<8 | g2;
    return g;
}


double MPU9520A_READ_AXIS_IN_G(int Axie)
{
    uint8_t x =0;
    double acceleration = 0;
    double g = 0;
    double sum =0;
    double average_counter =20;
    x = MPU9520A_read(ACCEL_CONFIG);
    x = (~ACCEL_FS_MASK & x);
    double divisor = 1;
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
    for(int i=0;i <average_counter;i++)
    {
        acceleration = MPU9520A_READ_AXIS(Axie);
        g = acceleration/divisor;
        sum += g;
    }
    return sum/average_counter;
}


double MPU9520A_YZ_AXIS_IN_DEGREE()
{
    long double x = 0;
    long double y = 0;
    x = MPU9520A_READ_AXIS_IN_G(AXIE_X);
    y = MPU9520A_READ_AXIS_IN_G(AXIE_Y);
    double z = MPU9520A_READ_AXIS_IN_G(AXIE_Z);
    if (x >= 1) x = 1;
    if (y >= 1) y = 1;
    if (z >= 1) z = 1;
    double sinalfa = asin(y);
    double in_degree = ((sinalfa *360)/(2*M_PI));
    printf("Kąt w stopniach sin: %f\n", in_degree);
    double cosalfa = acos(y);
    double in_degree2 = ((cosalfa *360)/(2*M_PI));
    printf("Kąt w stopniach cos: %f\n", in_degree2);
    double tgalfa = atan2(y, z);
    double in_degree3 = ((tgalfa *360)/(2*M_PI));
    printf("Kąt w stopniach tg: %f\n", in_degree3);
    return in_degree3;
}