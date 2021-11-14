#include <stdio.h>


#define AccelerometrID 0x68

//Register name and addres 
#define CONFIG          0x1A
#define ACCEL_CONFIG    0x1C
#define ACCEL_CONFIG_2  0x1D
#define LP_ACCEL_ODR    0x1E
#define FIFO_EN         0x23
#define ACCEL_XOUT_H    0x3B
#define ACCEL_XOUT_L    0x3C
#define ACCEL_YOUT_H    0x3D
#define ACCEL_YOUT_L    0x3E
#define ACCEL_ZOUT_H    0x3F
#define ACCEL_ZOUT_L    0x40
#define WHO_AM_I        0x75


//CONFIG REGISTER
#define FIFO_MODE           0b00000010
//ACCEL CONFIG REGISTER
#define AX_ST_EN            0b00000001
#define AY_ST_EN            0b00000010 
#define AZ_ST_EN            0b00000100
#define ACCEL_FS_SEL_2G     0b00000000
#define ACCEL_FS_SEL_4G     0b00001000
#define ACCEL_FS_SEL_8G     0b00010000
#define ACCEL_FS_SEL_16G    0b00011000
#define ACCEL_FS_MASK       0b11100111




void MPU9520A_Init();
int MPU9520A_read(int Reg_adress);
void MPU9520A_write(int Reg_adress, int Data);
void MPU9520A_set_G_parameter(int g_param);
