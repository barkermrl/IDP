#include "electronics.h"
#include "decision.h"
#include "state.h"
#include <Arduino.h>
#include "line_following.h"
#include "spin.h"

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
        else if (atJunction && location == HOME && untilJunction == 0)
        {
            untilJunction++;
            ML->setSpeed(power);
            MR->setSpeed(power);
            while (atJunction)
            {
                getAtJunction();
                Serial.println("CHECKING JUNC");
            }
            return FOLLOW_LINE;
        }
        else if (atJunction && location == HOME && untilJunction == 1)
        {
            untilJunction++;
            location = TUNNEL;

            ML->setSpeed(power);
            MR->setSpeed(power);
            delay(2000);
            spin(RIGHT);
            updateSpeed();
            return FOLLOW_LINE;
        }
        else if (atJunction && untilJunction == 2 && location == TUNNEL)
        {
            MR->setSpeed(power);
            ML->setSpeed(power);
            delay(2000);
            spin(LEFT);
            direction = CLOCKWISE;
            untilJunction = 2;
            location = LOOP;
            for (int i = 0; i < 5000; i++)
            {
                lf4s();
            }
            numB = 2;
            numR = 2;
            return FOLLOW_LINE;
        } // End start phase

    case 2: // Deliver blue blocks
        // TODO
        return STOP; // End phase 2

    case 3: // Deliver red blocks
        // TODO
        return STOP; // End phase 3

    case 4: // Return home
        if (location == LOOP)
        {
            if (atJunction)
            {
                Serial.println("AT JUNC");
                if (direction == ANTICLOCKWISE)
                {
                    location = TUNNEL;
                    MR->setSpeed(power);
                    ML->setSpeed(power);
                    Serial.println("start Delay ANTI");
                    delay(2000);
                    Serial.println("done delay ANTI");
                    return SPIN_R;
                }
                else if (direction == CLOCKWISE)
                {
                    location = TUNNEL;
                    MR->setSpeed(power);
                    ML->setSpeed(power);
                    Serial.println("stat Delay");
                    delay(2000);
                    Serial.println("done delay");
                    if (RMOnLine() or LMOnLine())
                    {
                        return SPIN_L;
                    }
                }
            }
            else if (untilJunction == 2)
            {
                Serial.println("SPin");

                if (LMOnLine() or RMOnLine())
                {
                    toggleDirection();
                    getUntilJunc();
                    if (direction == ANTICLOCKWISE)
                    {
                        return SPIN_R;
                    }
                    return SPIN_L;
                }
                return FOLLOW_LINE;
            }
            else if (untilJunction == 0)
            {
                return FOLLOW_LINE;
            }
        }
        else if (location == TUNNEL)
        {
            if (atJunction)
            {
                location = HOME;
                ML->setSpeed(power);
                MR->setSpeed(power);
                delay(1000);
                getAtJunction();
                if (atJunction)
                {
                    return SPIN_L;
                }
            }
            return FOLLOW_LINE;
        }
        else if (location == HOME)
        {
            if (atJunction)
            {
                // Back at home square
                // Wait have a second to get into square
                MR->setSpeed(power);
                ML->setSpeed(power);
                delay(5000);
                return FINISH;
            }
            else
            {
                return FOLLOW_LINE;
            }
        } // End phase 4

    case 5: // Does something?
        
        return STOP; // End phase 5

    default: // Lost!
        Serial.println("PANIC!");
        return PANIC;
    }
}

void toggleDirection()
{
    if (direction == CLOCKWISE)
    {
        direction = ANTICLOCKWISE;
    }
    else if (direction == ANTICLOCKWISE)
    {
        direction = CLOCKWISE;
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