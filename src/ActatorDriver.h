#include "AccelerometerMPU9250A.h"
#include <wiringPi.h>
#include <softPwm.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <stdio.h>


// Pins
#define R_EN  17    // Physical 11
#define L_EN  27    // Physical 13
#define RPWM  22    // Physical 15
#define LPWM  6     // Physical 31
#define R_IS  12    // Psyhical 32
#define L_IS  13    // Psyhical 33


void Actuator_setup();
void Actuator_up();
void Actuator_down();
void Actuator_angle(double angle);
void Actuator_Stop();