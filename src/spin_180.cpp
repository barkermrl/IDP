#ifdef SPIN_180

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
}

void loop()
{
    //Function to do a 180* turn (Assuming midde sensor comes of the line during the turn)
    if (digitalRead(ls2) == LOW)
    {
        M1->run(FORWARD);
        M2->run(BACKWARD);
        M1->setSpeed(150);
        M2->setSpeed(150);
        while (digitalRead(ls2) == LOW)
        {
            delay(100);
        }
    }
    bool x = true;
    while (x == true)
    {
        if (digitalRead(ls2) == LOW)
        {
            M1->run(FORWARD);
            M2->run(FORWARD);
            M1->setSpeed(150);
            M2->setSpeed(150);
            x = false;
        }
    }
}

#endif