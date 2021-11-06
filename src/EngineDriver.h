#include <stdio.h>

#define FirstEnginePul 17       //physical 11
#define FirstEngineDir 6        //physical 31
#define FirstEngineEnable 19    //physical 35
#define SecondEnginePul 8       //physical 24
#define SecondEngineDir 7       //physical 26
#define SecondEngineEnable 16   //physical 36

#define STEPINCYCLE 400

enum Engine{
    FirstEngine,
    SecondEngine
};

void togglepin(int pinNumber);

void EngineDriver_Init();
void ChangeDirection(int Engine);
/*angle in degrees */
void RunFirstEngine(float angle);
