#include <Arduino.h>
#include "electronics.h"
#include "spin.h"
#include "line_following.h"
#include "state.h"
#define turnThresh 200

void lf1s()
{
    //Single swtich
    if (LMOnLine() && change == false)
    {
        delay(10);
        if (LMOnLine())
        { //to make sure the "low" reading isnt a sudden random drop
            ML->setSpeed(power + kw * dir);
            MR->setSpeed(power - kw * dir);
            change = true;
        }
    }
    if (LMOnLine() && change == true)
    {
        if (kw <= power)
        {
            kw = kw + 1;
            ML->setSpeed(power + kw * dir);
            MR->setSpeed(power - kw * dir);
        }
    }

    if (!LMOnLine() && change == true)
    {
        delay(10);
        if (!LMOnLine())
        { //to make sure the "high" reading isnt a sudden random spike
            toggleDir();
            kw = kw_min;
            ML->setSpeed(power + kw * dir);
            MR->setSpeed(power - kw * dir);
            change = false;
            delay(50);
        }
    }
}

void followCurve() //function to spin on the curve if the kw is too high
{
    if (kw >= turnThresh && dir == R)
    {
        MR->setSpeed(power);
        ML->setSpeed(power);
        delay(500);
        kw = kw_min;
        Serial.println("Left");
        spin(LEFT);
    }
    else if (kw >= turnThresh && dir == L)
    {
        MR->setSpeed(power);
        ML->setSpeed(power);
        delay(1000);
        kw = kw_min;
        Serial.println("Right");
        spin(RIGHT);
    }
}

void lf4s()
{
    // Line is 2cm wide, Targets are 7.5cm wide
    if (dir == R && LMOnLine())
    {
        toggleDir();
        kw = kw_min;
        updateSpeed();
    }
    if (dir == L && RMOnLine())
    {
        kw = kw_min;
        toggleDir();
        updateSpeed();
    }
    else
    {
        kw = kw + 0.7;
        updateSpeed();
        // Serial.println(kw);
    }
}

void toggleDir()
{
    if (dir == L)
    {
        dir = R;
    }
    else if (dir = R)
    {
        dir = L;
    }
}