#include <Arduino.h>
#include "electronics.h"
#include "line_following.h"
#include "state.h"
#include "spin.h"

void spin(spin_direction_status spin_direction) //direction tells you wether or not you should spin to the right (-1) or to the left (+1)
{
    //Function to do a 180* turn (Assuming midde sensor comes off the line during the turn)
    if (spin_direction == LEFT)
    { //spinning to the left
        MR->run(FORWARD);
        ML->run(BACKWARD);
        ML->setSpeed(power);
        MR->setSpeed(power);
        Serial.println("started Spinning");
    }
    else //spinning to the right
    {
        MR->run(BACKWARD);
        ML->run(FORWARD);
        ML->setSpeed(power);
        MR->setSpeed(power);
    }
    if (RMOnLine() or LMOnLine())
    {
        while (RMOnLine() or LMOnLine())
        {
            delay(1000);
            Serial.println("Spinning");
        }
    }

    while (true)
    {
        if (RMOnLine() && spin_direction == LEFT)
        {
            MR->run(FORWARD);
            ML->run(FORWARD);
            ML->setSpeed(0);
            MR->setSpeed(0);
            break;
        }
        if (LMOnLine() && spin_direction == RIGHT)
        {
            MR->run(FORWARD);
            ML->run(FORWARD);
            ML->setSpeed(0);
            MR->setSpeed(0);
            break;
        }
    }
}
