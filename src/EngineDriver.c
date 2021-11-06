#include <wiringPi.h>
#include "EngineDriver.h"


/* TOOLS */

void togglepin(int pinNumber)
{
    if(digitalRead(pinNumber)==0)
    {
        digitalWrite(pinNumber,HIGH);
    }
    else if(digitalRead(pinNumber)==1)
    {
        digitalWrite(pinNumber,LOW);
    }
}

/*Engine */

void EngineDriver_Init()
{
    wiringPiSetupGpio();
    pinMode(FirstEnginePul,OUTPUT);         //physical 11
    digitalWrite(FirstEnginePul,LOW);
    pinMode(FirstEngineDir,OUTPUT);         //physical 31
    digitalWrite(FirstEngineDir,LOW);
    pinMode(FirstEngineEnable,OUTPUT);      //physical 35
    digitalWrite(FirstEngineEnable,LOW);
    pinMode(SecondEnginePul,OUTPUT);         //physical 24
    digitalWrite(SecondEnginePul,LOW);
     pinMode(SecondEngineDir,OUTPUT);         //physical 26
    digitalWrite(SecondEngineDir,LOW);
    pinMode(FirstEngineEnable,OUTPUT);      //physical 36
    digitalWrite(SecondEngineEnable,LOW);
}

void ChangeDirection(int Engine)
{
    if(Engine ==0)
    {
        printf("pierwszy silnik!\n");
        togglepin(FirstEngineDir);
    }
    else if(Engine ==1)
    {
        printf("Drugi silnik!\n");
        togglepin(SecondEngineDir);
    }
    else printf("bład :/\n");
}

void RunFirstEngine(float angle)    //TODO: Check if this code working in normal engine
{
    int Steps = (angle/360)*STEPINCYCLE;
    printf("Ilość krókw = %d\n",Steps);
}