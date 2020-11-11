#if LINE_FOLLOWER_SINGLE_SWITCH

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

    M2->setSpeed(150 + kw * dir);
    M1->setSpeed(150 - kw * dir);
}

void loop()
{
    //Single swtich
    if (digitalRead(ls2) == LOW && change == false)
    {
        delay(50);
        if (digitalRead(ls2) == LOW)
        { //to make sure the "low" reading isnt a sudden random drop
            M2->setSpeed(150 + kw * dir);
            M1->setSpeed(150 - kw * dir);
            change = true;
        }
    }
    if (digitalRead(ls2) == HIGH && change == true)
    {
        delay(50);
        if (digitalRead(ls2) == HIGH)
        { //to make sure the "high" reading isnt a sudden random spike
            dir = -1 * dir;
            M2->setSpeed(150 + kw * dir);
            M1->setSpeed(150 - kw * dir);
            change = false;
            delay(50);
        }
    }
}

#endif