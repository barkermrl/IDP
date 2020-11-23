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
            untilJunction++; //setting untillJunc to 1
            ML->setSpeed(power);
            MR->setSpeed(power);
            while (atJunction)
            {
                getAtJunction();
                Serial.println("AT JUNC");
            }
            return FOLLOW_LINE;
        }
        else if (atJunction && location == HOME && untilJunction == 1)
        {
            untilJunction++; //setting untillJunc to 2
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
            spin(RIGHT);
            direction = ANTICLOCKWISE;
            untilJunction = 2;
            location = LOOP;
            start = 0;
            return FOLLOW_LINE;
        } // End start phase

    case 2: // Deliver blue blocks, phase starts when we reach the T junction and turn RIGHT

        //While in loop:

        //Searching for Blue
        if (location == LOOP && currentBlock == EMPTY && atBlock == 0)
        {
            if (!atJunction) //if you are not at a junction and do not have a block
            {
                return FOLLOW_LINE;
            }
            if (atJunction)
            {
                skipJunc();
                return FOLLOW_LINE;
            }
        }

        else if (location == LOOP && currentBlock == EMPTY && atBlock == 1) //detected block so decide wether or not to pick up based on colour and _R
        {
            //PICK UP BLOCK and IDENTIFY
            closeMechanism();
            if (colour1read() == 0)
            {
                currentBlock == BLUE;
                if (direction == CLOCKWISE)
                {
                    spin(RIGHT);
                    direction = ANTICLOCKWISE;
                }
                else
                {
                    spin(LEFT);
                    direction = CLOCKWISE;
                }
                untilJunction = 2 - untilJunction;
            }
            else if (colour1read() == 1 && _R == 0)
            {
                openMechanism();
                _R == 1;
                ML->run(BACKWARD);
                MR->run(BACKWARD);
                ML->setSpeed(power);
                MR->setSpeed(power);
                delay(3000);
                if (direction == CLOCKWISE)
                {
                    spin(RIGHT);
                    direction = ANTICLOCKWISE;
                }
                else
                {
                    spin(LEFT);
                    direction = CLOCKWISE;
                }
                untilJunction = 2 - untilJunction;
                return FOLLOW_LINE;
            }
            else if (colour1read() == 1 && _R == 1)
            {
                currentBlock == RED;
                if (direction == CLOCKWISE)
                {
                    spin(RIGHT);
                    direction = ANTICLOCKWISE;
                }
                else
                {
                    spin(LEFT);
                    direction = CLOCKWISE;
                }
                untilJunction = 2 - untilJunction;
                return FOLLOW_LINE;
            }
        }

        else if (location == LOOP && currentBlock == RED && blockAhead == 0)
        {
            if (!atJunction)
            {
                return FOLLOW_LINE;
            }
            else
            {
                skipJunc();
            }
        }

        else if (location == LOOP && currentBlock == RED && blockAhead == 1)
        {
            ML->run(BACKWARD);
            MR->run(BACKWARD);
            ML->setSpeed(power);
            MR->setSpeed(power);
            delay(1000);
            openMechanism();
            delay(2000);
            if (direction == CLOCKWISE)
            {
                spin(RIGHT);
                direction = ANTICLOCKWISE;
            }
            else
            {
                spin(LEFT);
                direction = CLOCKWISE;
            }
            untilJunction = 2 - untilJunction;
            currentBlock = EMPTY;
            return FOLLOW_LINE;
        }

        else if (location == LOOP && currentBlock == BLUE) //Have the blue block, looking for target
        {
            if (!atJunction)
            {
                return FOLLOW_LINE;
            }
            else if (atJunction && untilJunction == 0)
            {
                ML->setSpeed(power);
                MR->setSpeed(power);
                delay(2000);
                if (direction == ANTICLOCKWISE)
                {
                    spin(RIGHT);
                    return FOLLOW_LINE;
                }
                else
                {
                    spin(LEFT);
                    return FOLLOW_LINE;
                }
                location = TUNNEL;
                direction = NONE;
            }
            else if (atJunction && untilJunction != 0)
            {
                skipJunc();
                return FOLLOW_LINE;
            }
        }

        else if (location == TUNNEL && currentBlock == BLUE) //have a blue block and going to the target
        {
            if (!atJunction)
            {
                return FOLLOW_LINE;
            }
            else
            {
                ML->setSpeed(power);
                MR->setSpeed(power);
                delay(1000);
                spin(RIGHT);
                location = BLUE_DELIVERY;
                if (numB == 0)
                {
                    untilJunction = 2;
                }
                else if (numB == 1)
                {
                    untilJunction = 1;
                }
                return FOLLOW_LINE;
            }
        }

        else if (location == BLUE_DELIVERY && currentBlock == BLUE)
        {
            if (!atJunction)
            {
                return FOLLOW_LINE;
            }
            if (atJunction && direction == NONE)
            {
                ML->run(FORWARD);
                MR->run(FORWARD);
                ML->setSpeed(power);
                MR->setSpeed(power);
                delay(2000);
                spin(LEFT);
                direction = CLOCKWISE;
                untilJunction = untilJunction - 1;
            }
            else if (atJunction && untilJunction == 1 && direction == CLOCKWISE)
            {
                ML->run(FORWARD);
                MR->run(FORWARD);
                ML->setSpeed(power);
                MR->setSpeed(power);
                delay(2000);
                spin(RIGHT);
                untilJunction = untilJunction - 1;
            }
            else if (atJunction && untilJunction == 0)
            {
                if (numB == 0)
                {
                    ML->setSpeed(0);
                    MR->setSpeed(0);
                    openMechanism();
                    currentBlock = EMPTY;
                    numB = numB + 1;
                    ML->run(BACKWARD);
                    MR->run(BACKWARD);
                    ML->setSpeed(power);
                    MR->setSpeed(power);
                    delay(3000);
                    spin(RIGHT);
                    direction = NONE;
                    untilJunction = 1;
                    return FOLLOW_LINE;
                }
                if (numB == 1)
                {
                    ML->setSpeed(0);
                    MR->setSpeed(0);
                    openMechanism();
                    currentBlock = EMPTY;
                    complete2 = true;
                    ML->run(BACKWARD);
                    MR->run(BACKWARD);
                    ML->setSpeed(power);
                    MR->setSpeed(power);
                    delay(3000);
                    spin(RIGHT);
                    ML->run(BACKWARD);
                    MR->run(BACKWARD);
                    ML->setSpeed(power);
                    MR->setSpeed(power);
                    delay(2500);
                    direction = NONE;
                    untilJunction = 1;
                    return FOLLOW_LINE;
                }
            }
        }

        else if (location == BLUE_DELIVERY && currentBlock == EMPTY)
        {
            if (!atJunction)
            {
                return FOLLOW_LINE;
            }
            else if (atJunction && untilJunction == 1)
            {
                ML->run(FORWARD);
                MR->run(FORWARD);
                ML->setSpeed(power);
                MR->setSpeed(power);
                delay(2000);
                spin(RIGHT);
                untilJunction = 0;
                return FOLLOW_LINE;
            }
            else if (atJunction && untilJunction == 0)
            {
                location = TUNNEL;
                return FOLLOW_LINE;
            }
        }
        else if (location == TUNNEL && currentBlock == EMPTY)
        {
            if (!atJunction)
            {
                return FOLLOW_LINE;
            }
            else
            {
                location = LOOP;
                direction = ANTICLOCKWISE;
                ML->run(FORWARD);
                MR->run(FORWARD);
                ML->setSpeed(power);
                MR->setSpeed(power);
                delay(2000);
                spin(RIGHT);
                if (complete2 == true)
                {
                    numB = 2;
                }
                _R = 0;
                return FOLLOW_LINE;
            }
        }

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