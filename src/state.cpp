#include <Arduino.h>
#include "electronics.h"
#include "state.h"
#include "line_following.h"

int threshold = 50; // max power_difference value when robot is still on straight
bool on_straight; // true if the robot is going straight
bool outer_on_line; // true if either of the outer sensors are on the line

//State functions that contains all state variables
void pidGetAtJunction()
{
    // Checks if the robot is going straight (for T-junctions)
    // i.e. the magnitude of power_difference is less than threshold
    on_straight = power_difference > -threshold and power_difference < threshold;
    outer_on_line = ROnLine() or LOnLine();

    if (on_straight and outer_on_line)
    {
        atJunction = true;
        return;
    }

    // else if at least three sensors are on the line, we're at a junction
    else if (LOnLine() + LMOnLine() + RMOnLine() + ROnLine() >= 3)
    {
        atJunction = true;
        return;
    }

    // if neither of the previous two conditions are met, we're not at a junction
    else
    {
        atJunction = false;
        return;
    }
}

void getAtJunction()
{
    if ((ROnLine() && location == LOOP && direction == ANTICLOCKWISE) or (ROnLine() && location != LOOP))
    {
        atJunction = true;
        // Serial.println("JUNC DETECTED");
    }
    else if ((LOnLine() && location == LOOP && direction == CLOCKWISE) or (LOnLine() && location != LOOP))
    {
        atJunction = true;
        // Serial.println("JUNC DETECTED");
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
