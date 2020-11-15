#include <Arduino.h>
#include "variables.h"
#include "electronics.h"

void spin180()
{
    //Function to do a 180* turn (Assuming midde sensor comes of the line during the turn)
    if (RMOnLine())
    {
        MR->run(FORWARD);
        ML->run(BACKWARD);
        MR->setSpeed(power);
        ML->setSpeed(power);
        while (RMOnLine())
        {
            delay(100);
        }
    }
    for (int i = 0; i <= 10000, i++;)
    {
        if (RMOnLine())
        {
            MR->run(FORWARD);
            ML->run(FORWARD);
            ML->setSpeed(0);
            MR->setSpeed(0);
            break;
        }
    }
}

void spin90Left()
{
    // Robot spins 90 left

    /***********************
    TODO
    ***********************/
}

void spin90Right()
{
    // Robot spins 90 right

    /***********************
    TODO
    ***********************/
}
