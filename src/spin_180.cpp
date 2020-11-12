#include <Arduino.h>
#include "variables.h"
#include "electronics.h"

void spin_180()
{
    //Function to do a 180* turn (Assuming midde sensor comes of the line during the turn)
    if (centerOnLine())
    {
        MR->run(FORWARD);
        ML->run(BACKWARD);
        MR->setSpeed(power);
        ML->setSpeed(power);
        while (centerOnLine())
        {
            delay(100);
        }
    }
    bool x = true;
    while (x == true)
    {
        if (centerOnLine())
        {
            MR->run(FORWARD);
            ML->run(FORWARD);

            ML->setSpeed(power + kw * dir);
            MR->setSpeed(power - kw * dir);
            x = false;
        }
    }
}
