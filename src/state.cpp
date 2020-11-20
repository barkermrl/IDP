#include <Arduino.h>
#include "electronics.h"
#include "state.h"
#include "line_following.h"

//State functions that contains all state variables

void getAtJunction()
{
    if (ROnLine())
    {
        atJunction = true;
        Serial.println("JUNC DETECTED");
    }
    else if (LOnLine())
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
