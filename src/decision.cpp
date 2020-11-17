#include "electronics.h"
#include "decision.h"
#include "state.h"
#include <Arduino.h>
#include "line_following.h"

int makeDecision()
{
    // start phase
    if (phase == 1 && !atJunction){
        return FOLLOW_LINE;
    }
    else if (phase == 1 && atJunction && untilJunction < 2){
        untilJunction = untilJunction +1;

        ML -> setSpeed(power);
        MR -> setSpeed(power);
        
        while (atJunction){
            getAtJunction();
        }
        return FOLLOW_LINE;
    }
    else if (phase == 1 && atJunction && untilJunction == 2){
        start = 0;
        tunnelSide = 1;
        return FOLLOW_LINE;
    // End start phase

    //Other phases currently
    if (phase == 2 or phase == 3 or phase ==4){
        return STOP;
    }
    }
}