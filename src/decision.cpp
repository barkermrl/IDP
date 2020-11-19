#include "electronics.h"
#include "decision.h"
#include "state.h"
#include <Arduino.h>
#include "line_following.h"

output_status makeDecision()
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
        updateSpeed();
        return FOLLOW_LINE;
    }
    else if (phase == 1 && atJunction && untilJunction == 2){
        start = 0;
        tunnelSide = 1;
        return STOP;
    // End start phase

    //Other phases currently
    if (phase == 2 or phase == 3 or phase == 4 or phase ==5){
        return STOP;
    }
    }
}

void getPhase(){

    if (start == 1 && numB == 0 && numR == 0){
        phase = 1; //start phase (getting to the oval)
    }
    else if (start == 0 && numB < 2 && numR == 0){
        phase = 2; //second phase (delivering the blue blocks to the square)
    }
    else if (start == 0 && numB == 2 && numR <2){
        phase = 3; //third phase (delivering the red blocks to their targets)
    }
    else if (start ==1 && numB ==2 && numR == 2){
        phase = 4; //4th phase (return to start area)
    }
    else
    {
        phase = 5;
    }
    
}