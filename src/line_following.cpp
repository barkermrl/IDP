#include <Arduino.h>
#include "electronics.h"
#include "spin.h"
#include "line_following.h"
#include "state.h"
#define turnThresh 200

void lf4s()
{
    // Line is 2cm wide, Targets are 7.5cm wide
    if (dir == R && (LMOnLine() or (kw > 150 && location != TUNNEL) or (kw > 100 && location == TUNNEL)))
    {
        toggleDir();

        kw = kw_min;

        updateSpeed();
    }
    if (dir == L && (RMOnLine() or (kw > 150 && location != TUNNEL) or (kw > 100 && location == TUNNEL)))
    {
        if (location == TUNNEL or BLUE_DELIVERY)
        {
            kw = 20;
        }
        else
        {
            kw = kw_min;
        }
        toggleDir();
        updateSpeed();
    }
    else
    {
        //followCurve();
        if (location == LOOP)
        {
            kw = kw + 0.5;
        }
        else if (location == HOME)
        {
            kw = kw + 0.7;
        }
        else if (location == TUNNEL)
        {
            kw = kw + 0.2;
        }
        if (kw > 250 && location != TUNNEL)
        {
            Serial.print("off line");
        }
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
                delay(2000);
                spin(LEFT);
                lf4s();
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
        else if (untilJunction == 1)
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
            }
            if (direction == CLOCKWISE)
            {
                MR->setSpeed(power);
                ML->setSpeed(power);
                while (atJunction)
                {
                    getAtJunction();
                }
                delay(2000);
                spin(RIGHT);
            }
        }
        else if (untilJunction == 0)
        {
            MR->setSpeed(power);
            ML->setSpeed(power);
            while (atJunction)
            {
                getAtJunction();
            }
            lf4s();
            untilJunction = 2;
        }
    }
}