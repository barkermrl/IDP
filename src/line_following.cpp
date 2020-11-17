#include <Arduino.h>
#include "electronics.h"
#include "spin.h"
#include "line_following.h"
#include "state.h"
#define turnThresh 150

void lf1s()
{
    //Single swtich
    if (LMOnLine() && change == false)
    {
        delay(50);
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
        delay(50);
        if (!LMOnLine())
        { //to make sure the "high" reading isnt a sudden random spike
            dir = -1 * dir;
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
    if (kw >= turnThresh && dir == -1){
        MR ->setSpeed(power);
        ML ->setSpeed(power);
        delay(500);
        directionSPIN = -1;
        spin180();
    }
    else if(kw >= turnThresh && dir == 1){
        MR ->setSpeed(power);
        ML ->setSpeed(power);
        delay(500);
        directionSPIN = 1;
        spin180();
    }
}

void lf4s()
{
    // Line is 2cm wide, Targets are 7.5cm wide
    if (dir == -1 && LMOnLine())
    {
        dir = dir * -1;
        kw = kw_min;
        updateSpeed(power, kw, dir);
    }
    if (dir == 1 && RMOnLine())
    {
        kw = kw_min;
        dir = dir * -1;
        updateSpeed(power, kw, dir);
    }
    else
    {
        kw = kw + 0.7;
        updateSpeed(power, kw, dir);
        // Serial.println(kw);
    }
}
