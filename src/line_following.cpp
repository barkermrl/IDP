#include <Arduino.h>
#include "electronics.h"
#include "spin.h"
#include "line_following.h"
#include "state.h"
#define turnThresh 200

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
        //followCurve();
        kw = kw + 0.7;
        updateSpeed();
        // Serial.println(kw);
    }
}

void toggleDir()
{
    //Serial.println("Toggle Direction");
    if (dir == L)
    {
        dir = R;
    }
    else if (dir = R)
    {
        dir = L;
    }
}

void skipJunc()
{
    if (atJunction && location == LOOP)
    {
        if (untilJunction == 2)
        {
            untilJunction = untilJunction - 1;
            if (direction == ANTICLOCKWISE)
            {
                MR->setSpeed(power);
                ML->setSpeed(power);
                while (atJunction)
                {
                    getAtJunction();
                }
                delay(1000);
                spin(LEFT);
            }
            else
            {
                MR->setSpeed(power);
                ML->setSpeed(power);
                while (atJunction)
                {
                    getAtJunction();
                }
            }
        }
        if (untilJunction == 1)
        {
            untilJunction = untilJunction - 1;
            if (direction == ANTICLOCKWISE){
                MR->setSpeed(power);
                ML->setSpeed(power);
                while (atJunction)
                {
                    getAtJunction();
                }
            }
            if (direction == CLOCKWISE){
                MR->setSpeed(power);
                ML->setSpeed(power);
                while (atJunction)
                {
                    getAtJunction();
                }
                delay(1000);
                spin(RIGHT);
            }
        }
        if (untilJunction == 0){
                untilJunction = 2;
                MR->setSpeed(power);
                ML->setSpeed(power);
                while (atJunction)
                {
                    getAtJunction();
                }
        }
    }
}