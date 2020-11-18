#include <Arduino.h>
#include "electronics.h"
#include "line_following.h"
#include "state.h"

void spin180() //direction tells you wether or not you should spin to the right (-1) or to the left (+1)
{
    //Function to do a 180* turn (Assuming midde sensor comes of the line during the turn)
    if (abs(directionSPIN) == 1){
        if (RMOnLine() or LMOnLine()) //occurs when either one of the sensors is on the line
        {
            if (directionSPIN == 1){ //spinning to the left
                MR->run(FORWARD);
                ML->run(BACKWARD);
                ML ->setSpeed(power);
                MR -> setSpeed(power);
            }
            else //spinning to the right
            {
                MR->run(BACKWARD);
                ML->run(FORWARD);
                ML ->setSpeed(power);
                MR -> setSpeed(power);
            }
            while (RMOnLine() or LMOnLine())
            {
                delay(100);
            }
        }

        while (true)
        {
            if (RMOnLine() && directionSPIN == 1)
            {
                MR->run(FORWARD);
                ML->run(FORWARD);
                ML->setSpeed(0);
                MR->setSpeed(0);
                delay(10000);
                break;
            }
            if (LMOnLine() && directionSPIN == -1)
            {
                MR->run(FORWARD);
                ML->run(FORWARD);
                ML->setSpeed(0);
                MR->setSpeed(0);
                delay(10000);
                break;
            }
        }
    }
}
