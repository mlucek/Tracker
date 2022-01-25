#include <wiringPi.h>
#include "EngineDriver.h"

/* TOOLS */

void togglepin(int pinNumber)
{
    if (digitalRead(pinNumber) == 0)
    {
        digitalWrite(pinNumber, HIGH);
    }
    else if (digitalRead(pinNumber) == 1)
    {
        digitalWrite(pinNumber, LOW);
    }
}

/*Engine */

void EngineDriver_Init()
{
    wiringPiSetupGpio();
    pinMode(15, OUTPUT); //physical 11
    digitalWrite(FirstEnginePul, HIGH);
    pinMode(FirstEngineDir, OUTPUT); //physical 31
    digitalWrite(FirstEngineDir, HIGH);
    pinMode(FirstEngineEnable, OUTPUT); //physical 35
    digitalWrite(FirstEngineEnable, HIGH);
}

void ChangeDirection()
{
    printf("pierwszy silnik!\n");
    togglepin(FirstEngineDir);
}

void RunFirstEngine(float angle) //TODO: Check if this code working in normal engine
{
    int Steps = (angle / 360) * STEPINCYCLE *2 * 2.1;
    printf("Ilość krókw = %d\n", Steps);
    for (size_t i = 0; i < Steps; i++)
    {
        togglepin(FirstEnginePul);
        delay(75); //To turn around ~30 sec
    }
}

void Disable_EnableEngine(int Engine, int Availability)
{
    if (Availability == Disenable)
    {
        digitalWrite(FirstEngineEnable, LOW);
    }
    else if (Availability == Enable)
    {
        digitalWrite(FirstEngineEnable, HIGH);
    }
}
