#include <stdio.h>

#define FirstEnginePul 15       //physical 11
#define FirstEngineDir 9        //physical 31
#define FirstEngineEnable 11    //physical 35


#define STEPINCYCLE 400

enum Engine{
    FirstEngine,
    SecondEngine
};

enum Availability{
    Disenable,
    Enable
};

void togglepin(int pinNumber);
void EngineDriver_Init();
void ChangeDirection();
/*angle in degrees */
void RunFirstEngine(float angle);
void Disable_EnableEngine(int Engine, int Availability);
