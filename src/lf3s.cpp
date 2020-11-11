#ifdef LINE_FOLLOWER_3_SWITCH

#include <Arduino.h>
#include <Wire.h>
#include "misc_func.h"
#include "variables.h"

void setup()
{
    Serial.begin(9600); // set up Serial library at 9600 bps
    Serial.println("Adafruit Motorshield v2 - DC Motor test!");
    AFMS.begin(); // create with the default frequency 1.6KHz

    pinMode(ls1, INPUT); //left
    pinMode(ls2, INPUT); //centre
    pinMode(ls3, INPUT); //right

    M1->run(FORWARD);
    M2->run(FORWARD);

    M2->setSpeed(150);
    M1->setSpeed(150);
}

void loop()
{
    // "running average method"

    //read sensor values and add their values into the lists
    update(&avg1[0], &avg2[0], &avg3[0], 10, ls1, ls2, ls3);

    // loop to find averages of the lists
    double av[3] = {0, 0, 0};
    for (int i = 0; i < 10; i++)
    {
        av[0] += avg1[i];
        av[1] += avg2[i];
        av[2] += avg3[i];
    }
    av[0] = av[0] / 10;
    av[1] = av[1] / 10;
    av[2] = av[2] / 10;

    //control algorithm
    double e = av[0] + av[1] - av[2]; // e = av1 + av2 - ev3
    double K = kp * e;

    //change motor powers
    M2->setSpeed(150 - K);
    M1->setSpeed(150 + K);
    delay(100);
}

#endif