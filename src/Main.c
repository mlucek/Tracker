#include "EngineDriver.h"
#include <stdio.h>
#include <wiringPi.h>


void test(int pinNumber)
{
    wiringPiSetupGpio();
    pinMode(pinNumber,OUTPUT);
    delay(5);
}

void test2(int pinNumber)
{
    wiringPiSetupGpio();
    pinMode(pinNumber,OUTPUT);
}

int main()
{
    EngineDriver_Init();
    ChangeDirection(FirstEngine);
    ChangeDirection(SecondEngine);
    RunFirstEngine(180);
    RunFirstEngine(360);
    RunFirstEngine(13);

}