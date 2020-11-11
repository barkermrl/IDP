#include <Arduino.h>
#include "variables.h"
#include "electronics.h"

void lf1s()
{
    //Single swtich
    if (!centerOnLine() && change == false)
    {
        delay(50);
        if (!centerOnLine())
        { //to make sure the "low" reading isnt a sudden random drop
            ML->setSpeed(power + kw * dir);
            MR->setSpeed(power - kw * dir);
            change = true;
        }
    }
    if (centerOnLine() && change == true)
    {
        delay(50);
        if (centerOnLine())
        { //to make sure the "high" reading isnt a sudden random spike
            dir = -1 * dir;
            ML->setSpeed(power + kw * dir);
            MR->setSpeed(power - kw * dir);
            change = false;
            delay(50);
        }
    }
}
