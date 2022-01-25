#include "ActatorDriver.h"



void Actuator_setup()
{
    wiringPiSetupGpio();
    pinMode(R_EN, OUTPUT);
    digitalWrite(R_EN, LOW);
    pinMode(L_EN, OUTPUT);
    digitalWrite(L_EN, LOW);
    pinMode(R_IS, INPUT);
    pullUpDnControl(R_IS, PUD_UP);
    pinMode(L_IS, INPUT);
    pullUpDnControl(L_IS, PUD_UP);
    softPwmCreate (RPWM, 0, 10);
    softPwmCreate (LPWM, 0, 10);
}


void Actuator_up()
{
    digitalWrite(L_EN, HIGH);
    digitalWrite(R_EN, HIGH);
    softPwmWrite (RPWM, 3);
}

void Actuator_down()
{
    digitalWrite(L_EN, HIGH);
    digitalWrite(R_EN, HIGH);
    softPwmWrite (LPWM, 3);
}

void Actuator_Stop()
{
    digitalWrite(L_EN, LOW);
    digitalWrite(R_EN, LOW);
    softPwmWrite (LPWM, 0);
    softPwmWrite (LPWM, 0);
}

void Actuator_angle(double angle)
{
    printf("Start Degre: %f \n ", MPU9520A_YZ_AXIS_IN_DEGREE());
    if (MPU9520A_YZ_AXIS_IN_DEGREE() >75)
    {
        Actuator_down();
        while(angle < MPU9520A_YZ_AXIS_IN_DEGREE()){}
        Actuator_Stop();
    }
    if (angle <=75)
    {
        if (angle < MPU9520A_YZ_AXIS_IN_DEGREE() -3)
        {
            Actuator_down();
            while(angle < MPU9520A_YZ_AXIS_IN_DEGREE()){}
            Actuator_Stop();
        }
        else if (angle > MPU9520A_YZ_AXIS_IN_DEGREE() +3)
        {
            Actuator_up();
            while(angle > MPU9520A_YZ_AXIS_IN_DEGREE()){}
            Actuator_Stop();
        }
    }
    printf("Stop Degre: %f \n ", MPU9520A_YZ_AXIS_IN_DEGREE());
}
