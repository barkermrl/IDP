#include <Arduino.h>
#include "electronics.h"
#include "state.h"
#include "line_following.h"

//State functions that contains all state variables

void getAtJunction()
{
    if ((ROnLine() && location == LOOP && direction == ANTICLOCKWISE) or (ROnLine() && location != LOOP))
    {
        atJunction = true;
        Serial.println("JUNC DETECTED");
    }
    else if ((LOnLine() && location == LOOP && direction == CLOCKWISE) or (LOnLine() && location != LOOP))
    {
        atJunction = true;
        Serial.println("JUNC DETECTED");
    }
    else
    {
        atJunction = false;
    }
}

void getUntilJunc()
{
    untilJunction = 2 - untilJunction;
}

void getBlockAhead()
{
    // TODO
    blockAhead = false;
}
