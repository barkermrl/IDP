#include <Arduino.h>
#include "variables.h"
#include "electronics.h"

void lf1s(){
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
    if (LMOnLine() && change == true){
        if (kw <= power){
            kw = kw +1;
            ML->setSpeed(power + kw * dir);
            MR->setSpeed(power - kw * dir);
        }     
    }

    if (!LMOnLine() && change == true){
        delay(50);
        if (!LMOnLine()){ //to make sure the "high" reading isnt a sudden random spike
            dir = -1 * dir;
            kw = kw_min;
            ML->setSpeed(power + kw * dir);
            MR->setSpeed(power - kw * dir);
            change = false;
            delay(50);
        }
    }
}