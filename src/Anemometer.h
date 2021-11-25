#include <wiringPi.h>
#include <pthread.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <stdio.h>


//#include <inttypes.h>



// Pins
#define ANE_PIN 25 

// Parameter to correct work of anemometer
#define NUMBER_OF_MEASUREMENT   10
#define RESET_LOOP_NUMBER       0


void cleanup(int signo);
void Anemometer_setup();
void check_Anemometer_speed();