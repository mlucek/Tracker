#include "Anemometer.h"



void cleanup(int signo)
{
    pinMode(ANE_PIN, OUTPUT);                //TODO: Check this
    pullUpDnControl(ANE_PIN, PUD_UP); 
    exit(0);
}


void check_Anemometer_speed()
{      
    static int loop_counter = RESET_LOOP_NUMBER;
    static int timediffstab[NUMBER_OF_MEASUREMENT];
    static int timediffnstab[NUMBER_OF_MEASUREMENT];
    long int sumoftimemesurements = 0;
    long int sumoftimemesurementns = 0;
    float averagemeasurementtime = 0;
    float averagewindspeed = 0;
    static int start = 0;
    static struct timespec lastCall;
    struct timespec thiscall;
    long int timediffs = 0;
    int timediffns = 0;
    clock_gettime(CLOCK_REALTIME, &thiscall);
    if (loop_counter > NUMBER_OF_MEASUREMENT -1) loop_counter =RESET_LOOP_NUMBER;
    if (start !=0)
    {
        timediffs = thiscall.tv_sec-lastCall.tv_sec;
        timediffns = thiscall.tv_nsec-lastCall.tv_nsec;
        if(timediffns <0)
        {
            timediffs --;
            timediffns = timediffns + 1000000000;
        }

        printf("sec%ld, nsec %ld\n", thiscall.tv_sec, thiscall.tv_nsec);
        printf("diffsec %ld, diffnsec %d\n", timediffs, timediffns);
        printf("start: %d\n", start);
        
    }
    if (start >0 && start <NUMBER_OF_MEASUREMENT)
    {
        timediffstab[loop_counter] = timediffs;
        timediffnstab[loop_counter] = timediffns/1000;  //nano to uicro
        start++;
        loop_counter++;
    }
    else if(start >= NUMBER_OF_MEASUREMENT)
    {
        timediffstab[loop_counter] = timediffs;
        timediffnstab[loop_counter] = timediffns/1000; //nano to uicro
        for(int i = 0;i < NUMBER_OF_MEASUREMENT;i++)
        {
            sumoftimemesurements += timediffstab[i];
            sumoftimemesurementns += timediffnstab[i];
            printf("timediffnstab[i]; %d\n", timediffnstab[i]);
        }
        averagemeasurementtime = ((float) sumoftimemesurements + ((float)sumoftimemesurementns / 1000000))/NUMBER_OF_MEASUREMENT;
        averagewindspeed = (1/averagemeasurementtime) *2.4f;
        printf("average time %f\n", averagemeasurementtime);
        printf("average speed %f\n", averagewindspeed);
        loop_counter++;
    }
    else start ++;
    delay(15);
    lastCall = thiscall;
}


void Anemometer_setup()
{
    wiringPiSetupGpio();

    pinMode(ANE_PIN, INPUT);                //TODO: Check this
    pullUpDnControl(ANE_PIN, PUD_UP); 

}


