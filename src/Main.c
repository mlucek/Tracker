#include "EngineDriver.h"
#include "AccelerometerMPU9250A.h"
#include "Anemometer.h"
#include "ActatorDriver.h"
#include <stdio.h>
#include <wiringPi.h>
#include <inttypes.h>

#define PI 3.14159265


int WORK_FLAG =0;

double actualltime(int hour, int minut, int second)
{
    return (hour + (minut/60) + (second/3600));
}

int main()
{
    double actuall_engine_angle = 0;
    double val = PI / 180;
    double B = 0;
    double E = 0;
    int day = 190;
    double NS = 50;
    double WEstandard = -15;
    double WElocal = -20;
    double declinaction = 0;
    double suntime = 0;
    double hourangle =0;
    double zenit = 0;
    double hourangleEW = 0;
    double sunyy = 0;
    double suny = 0;
    int C1 = 0;
    int C2 =0;
    int C3 = 0;
    int hour = 10;
    int min = 12;
    int sec = 19;


    printf("tu jestem");
    EngineDriver_Init();
    MPU9520A_Init();
    Anemometer_setup();
    Actuator_setup();
    printf("tu tez jestem");
    wiringPiISR(ANE_PIN, INT_EDGE_FALLING,check_Anemometer_speed);
    
    EngineDriver_Init();

    // while(TRUE)
    // {
    //     delay(500);
    //     printf("Degre: %f \n ", MPU9520A_YZ_AXIS_IN_DEGREE());
    //     //check_Anemometer_speed();
    //     //delay(500);

    // }
    delay(500);
    while(TRUE)
    {
        delay(500);
        printf("Degre: %f \n ", MPU9520A_YZ_AXIS_IN_DEGREE());
        if (WORK_FLAG == 0)
        {
            double timetable[30] = {9.25, 9.5, 9.75, 10, 10.25, 10.5, 10.75, 11, 11.25, 11.5, 11.75, 12, 12.25, 12.5, 12.75, 13,
                                    13.25, 13.5, 13.75, 14, 14.25, 14.5, 14.75, 15, 15.25, 15.5, 15.75, 16, 16.25, 16.5};
            for (int i =0; i<30;i++)
            {   
                B = (day-1)*(360/365);                                                                   //We can calculate this only one time a day
                E = 229.2*(0.000075+0.001868*cos(B*val)-0.032077*sin(B*val)-0.014615*cos(2*B*val)-0.04089*sin(2*B*val)); //We can calculate this only one time a day
                declinaction = 23.45*sin(((360*(284+day))/365)*val);
                suntime = 4*(WEstandard - WElocal)/60+E/60+timetable[i];//actualltime(hour, min, sec);
                printf("suntime: %f\n", suntime);
                hourangle = 15*(suntime-12);
                printf("hourangle: %f\n", hourangle);
                zenit = acos(((cos(NS*val)*cos(declinaction*val)*cos(hourangle*val))+(sin(NS*val)*sin(declinaction*val))))/val;
                hourangleEW = acos(tan(declinaction*val)/tan(NS*val))/val;
                sunyy = asin((sin(hourangle*val)*cos(declinaction*val))/sin(zenit*val))/val;
                if (abs(hourangle)<= hourangleEW) C1 = 1;
                else C1=-1;
                if ((NS-declinaction)>=0) C2=1;
                else C2=-1;
                if (hourangle>=0) C3=1;
                else C3=-1;
                suny = ((C1*C2*sunyy)+C3*((1-C1*C2)/2)*180)+90;
                printf("kat zenitu: %f, kat drugi: %f\n", zenit, suny);
                RunFirstEngine(suny - actuall_engine_angle);
                actuall_engine_angle = suny;
                Actuator_angle(zenit);

                printf("flag 0");
                delay(4000);
            }
            WORK_FLAG = 1;
        }
        else
        {
            Actuator_angle(0);
            printf("flag act");
            delay(3600000);
            printf("flag actuat");
            WORK_FLAG = 0;
            delay(1800000);
        }
    }
}
