#include "EngineDriver.h"
#include "AccelerometerMPU9250A.h"
#include "Anemometer.h"
#include <stdio.h>
#include <wiringPi.h>
#include <inttypes.h>



int main()
{
    EngineDriver_Init();
    ChangeDirection(FirstEngine);
    ChangeDirection(SecondEngine);
    MPU9520A_Init();
    Anemometer_setup();
    while(TRUE)
    {
        //printf("X AXis: %f \n ", MPU9520A_READ_AXIS_IN_G(AXIE_X));
        //printf("Y AXis: %f \n ", MPU9520A_READ_AXIS_IN_G(AXIE_Y));
        //printf("Z AXis: %f \n ", MPU9520A_READ_AXIS_IN_G(AXIE_Z));
        //MPU9520A_YZ_AXIS_IN_DEGREE();
        check_Anemometer_speed();
        delay(999);

    }
}
