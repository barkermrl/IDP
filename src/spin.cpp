#include <Arduino.h>
#include "electronics.h"

void spin180(int power, int direction) //direction tells you wether or not you should spin to the right (-1) or to the left (+1)
{
    //Function to do a 180* turn (Assuming midde sensor comes of the line during the turn)
    if (RMOnLine() or LMOnLine()) //occurs when either one of the sensors is on the line
    {
        if (direction == 1){
            MR->run(FORWARD);
            ML->run(BACKWARD);
        }
        else
        {
            MR->run(BACKWARD);
            ML->run(FORWARD);
        }
        MR->setSpeed(power);
        ML->setSpeed(power);
        while (RMOnLine() or LMOnLine())
        {
            delay(100);
        }
    }
    for (int i = 0; i <= 10000, i++;)
    {
        if (RMOnLine() && direction == 1)
        {
            MR->run(FORWARD);
            ML->run(FORWARD);
            ML->setSpeed(0);
            MR->setSpeed(0);
            break;
        }
        if (LMOnLine() && direction == -1)
        {
            MR->run(FORWARD);
            ML->run(FORWARD);
            ML->setSpeed(0);
            MR->setSpeed(0);
            break;
        }
    }
}
