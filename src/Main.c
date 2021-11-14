#include "EngineDriver.h"
#include "AccelerometerMPU9250A.h"
#include <stdio.h>
#include <wiringPi.h>



int main()
{
    EngineDriver_Init();
    ChangeDirection(FirstEngine);
    ChangeDirection(SecondEngine);
    MPU9520A_Init();
    printf("odczytana wartość %u", MPU9520A_read(ACCEL_CONFIG));
}