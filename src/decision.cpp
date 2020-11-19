#include "electronics.h"
#include "decision.h"
#include "state.h"
#include <Arduino.h>
#include "line_following.h"

output_status makeDecision()
{
    // Makes a decision based on the current phase and state variables.
    // Returns an output defined in output_status/
    switch (phase)
    {
    case 1: // Start phase
        if (!atJunction)
        {
            return FOLLOW_LINE;
        }
        else if (atJunction && untilJunction < 2)
        {
            untilJunction = untilJunction + 1;

            ML->setSpeed(power);
            MR->setSpeed(power);

            while (atJunction)
            {
                getAtJunction();
            }
            updateSpeed();
            return FOLLOW_LINE;
        }
        else if (atJunction && untilJunction == 2)
        {
            start = 0;
            location = LOOP;
            return STOP;
        } // End start phase
    
    case 2: // Deliver blue blocks
        // TODO
        return STOP;// End phase 2

    case 3: // Deliver red blocks
        // TODO
        return STOP; // End phase 3

    case 4: // Return home
        if (location == LOOP)
        {
            if (atJunction)
            {
                // if (direction == )
            }
            else if (untilJunction == 2)
            {
                direction = -1*direction;
                return SPIN_L;
            }
            else if (untilJunction == 0)
            {
                return FOLLOW_LINE;
            }
        }
        else if (location == TUNNEL)
        break; // End phase 4
    
    case 5: // Does something?
        // TODO
        return STOP; // End phase 5

    default: // Lost!
        Serial.println("PANIC!");
        return PANIC;
    } 
}

void getPhase()
{

    if (start == 1 && numB == 0 && numR == 0)
    {
        phase = 1; //start phase (getting to the oval)
    }
    else if (start == 0 && numB < 2 && numR == 0)
    {
        phase = 2; //second phase (delivering the blue blocks to the square)
    }
    else if (start == 0 && numB == 2 && numR < 2)
    {
        phase = 3; //third phase (delivering the red blocks to their targets)
    }
    else if (start == 1 && numB == 2 && numR == 2)
    {
        phase = 4; //4th phase (return to start area)
    }
    else
    {
        phase = 5;
    }
}