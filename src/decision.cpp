#include "electronics.h"
#include "decision.h"
#include "state.h"
#include <Arduino.h>
#include "line_following.h"
#include "output.h"

output_status makeDecision()
{
    // Makes a decision based on the current phase and state variables.
    // Returns an output defined in output_status/
    if (phase == 1)
    {
        // Start phase
        if (!atJunction)
        {
            return FOLLOW_LINE;
        }
        else if (atJunction && location == HOME && untilJunction == 0)
        {
            Serial.println("Phase 1: At 1st junction");
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
            //Serial.println("Phase 1: At second junction, moving to tunnel");
            untilJunction++; //setting untillJunc to 2
            location = TUNNEL;

            ML->setSpeed(power);
            MR->setSpeed(power);
            delay(2000);
            spin(RIGHT);
            return FOLLOW_LINE;
        }
        else if (atJunction && untilJunction == 2 && location == TUNNEL)
        {
            //Serial.println("Phase 1: At 3rd junction, entering the loop");
            MR->setSpeed(power);
            ML->setSpeed(power);
            delay(2500);
            spin(RIGHT);
            direction = ANTICLOCKWISE;
            untilJunction = 2;
            location = LOOP;
            start = 0;
            return FOLLOW_LINE;
        } // End start phase
    }
    else if (phase == 2)
    { // Deliver blue blocks, phase starts when we reach the T junction and turn RIGHT

        if (location == LOOP)
        {
            if (currentBlock == EMPTY)
            {
                if (!atBlock)
                {
                    if (!atJunction)
                    {
                        return FOLLOW_LINE;
                    }
                    else
                    {
                        skipJunc();
                        return FOLLOW_LINE;
                    }
                }
                // At block (empty)
                else
                {
                    for (int i = 0; i <= 10; i++)
                    {
                        lf4s();
                    }
                    grabBlock(false);//Pick up block
                    delay(500);
                    if (colour1read() == false) //if its blue
                    {
                        //Serial.println("Phase 2: Identify blue block");
                        currentBlock = BLUE;
                        updateLights(true);
                        delay(1000);
                        for (int i = 0; i < 20; i++)
                        {
                            lf4s();
                        }
                        if (direction == CLOCKWISE) //Spin
                        {
                            spin(RIGHT);
                            direction = ANTICLOCKWISE;
                        }
                        else //spin
                        {
                            spin(LEFT);
                            direction = CLOCKWISE;
                        }
                        //Serial.println("Phase 2: Done spinning (have block)");
                        untilJunction = 2 - untilJunction;
                        //Serial.print("Until junction: ");
                        return FOLLOW_LINE;
                    }
                    else if (colour1read() == true && _R == 0) //if its red and you havent already hit a red block
                    {
                        //Serial.println("Phase 2: Identify red block");
                        currentBlock = RED;
                        updateLights(false);
                        delay(1000);
                        openMechanism(); //release the block
                        currentBlock = EMPTY;
                        updateLights(true);
                        _R = 1; //to pick up and move the next red block we hit
                        ML->run(BACKWARD);
                        MR->run(BACKWARD);
                        ML->setSpeed(power);
                        MR->setSpeed(power);
                        delay(1000); //make sure block it outside the arms

                        if (direction == CLOCKWISE) //spin
                        {
                            spin(RIGHT);
                            direction = ANTICLOCKWISE;
                        }
                        else //spin
                        {
                            spin(LEFT);
                            direction = CLOCKWISE;
                        }
                        untilJunction = 2 - untilJunction;
                        return FOLLOW_LINE;
                    }

                    else if (colour1read() == true && _R == 1) //if the block is red and you already encountered a red block
                    {
                        //Serial.println("Phase 2: Identify 2nd red block");
                        currentBlock = RED; //pick it up
                        updateLights(false);
                        delay(1000);
                        updateLights(true);
                        for (int i = 0; i < 10; i++)
                        {
                            lf4s();
                        }
                        if (direction == CLOCKWISE) //spin
                        {
                            spin(RIGHT);
                            direction = ANTICLOCKWISE;
                        }
                        else //spin
                        {
                            spin(LEFT);
                            direction = CLOCKWISE;
                        }
                        untilJunction = 2 - untilJunction;
                        return FOLLOW_LINE;
                    }
                }
            }
            else if (currentBlock == RED)
            {
                if (blockAhead)
                {
                    ML->run(BACKWARD); //go back to leave space between the blocks
                    MR->run(BACKWARD);
                    ML->setSpeed(power);
                    MR->setSpeed(power);
                    delay(1000);
                    openMechanism();            //release the red block
                    delay(2000);                //reverse to let the block out of the area of the mechanism
                    if (direction == CLOCKWISE) //spin
                    {
                        spin(RIGHT);
                        direction = ANTICLOCKWISE;
                    }
                    else //spin
                    {
                        spin(LEFT);
                        direction = CLOCKWISE;
                    }
                    untilJunction = 2 - untilJunction;
                    currentBlock = EMPTY;
                    return FOLLOW_LINE;
                }
                else
                {
                    if (!atJunction)
                    {
                        return FOLLOW_LINE;
                    }
                    else if (untilJunction != 0) //if you hit a junction, skip it
                    {
                        skipJunc();
                        return FOLLOW_LINE;
                    }
                    else
                    {
                        for (int i = 0; i <= 30; i++)
                        {
                            lf4s();
                        }
                        ML->setSpeed(0);
                        MR->setSpeed(0);
                        openMechanism();
                        currentBlock = EMPTY;
                        redPosition = BOTH_RIGHT_BEFORE_DELIVERY;
                        updateLights(false);
                        delay(1000);
                        updateLights(true);
                        ML->run(BACKWARD);
                        MR->run(BACKWARD);
                        ML->setSpeed(power);
                        MR->setSpeed(power);
                        delay(1000);
                        if (direction == CLOCKWISE) //spin
                        {
                            spin(RIGHT);
                            direction = ANTICLOCKWISE;
                        }
                        else //spin
                        {
                            spin(LEFT);
                            direction = CLOCKWISE;
                        }
                        untilJunction = 2;
                        return FOLLOW_LINE;
                    }
                }
            }
            else if (currentBlock == BLUE)
            {
                if (!atJunction)
                {
                    return FOLLOW_LINE;
                }
                else if (untilJunction == 0) //if you are at the junction
                {
                    //pass it slightly to make spinning better
                    location = TUNNEL;
                    turnIntoTunnel();
                    return FOLLOW_LINE;
                }
                else if (untilJunction != 0) //if you drive over a red target, skip it
                {
                    skipJunc();
                    return FOLLOW_LINE;
                }
            }
        }
        else if (location == TUNNEL)
        {
            if (currentBlock == BLUE)
            {
                if (!atJunction)
                {
                    return FOLLOW_LINE;
                }
                else //hit the curved junction
                {
                    ML->setSpeed(power);
                    MR->setSpeed(power);
                    delay(2000);              // skip it then...
                    spin(RIGHT);              //...spin right
                    location = BLUE_DELIVERY; //set location to delivery area
                    if (numB == 0)            //depending on how many blocks we have delivered, set the delivery target
                    {
                        untilJunction = 2; //deep target
                    }
                    else if (numB == 1) //set delivery target
                    {
                        untilJunction = 1; //shallow target
                    }
                    return FOLLOW_LINE;
                }
            }
            else if (currentBlock == EMPTY)
            {
                if (!atJunction)
                {
                    return FOLLOW_LINE;
                }
                else
                {
                    location = LOOP;
                    direction = ANTICLOCKWISE;
                    untilJunction = 2;
                    ML->run(FORWARD);
                    MR->run(FORWARD);
                    ML->setSpeed(power);
                    MR->setSpeed(power);
                    delay(2000);
                    spin(RIGHT);
                    if (complete2 == true)
                    {
                        numB = 2;
                        complete2 = false;
                    }
                    _R = 0;
                    return FOLLOW_LINE;
                }
            }
        }
        else if (location == BLUE_DELIVERY)
        {
            if (currentBlock == BLUE) //entering Blue area with blue Block
            {
                if (!atJunction)
                {
                    return FOLLOW_LINE;
                }
                else if (numB == 0)
                {
                    deliverBlue1();
                }
                else if (numB == 1)
                {
                    deliverBlue2();
                    numB = 2;
                }
                moveUntilJunction();
                ML->setSpeed(power);
                MR->setSpeed(power);
                delay(2000);
                spin(LEFT);
                moveUntilJunction();
                ML->setSpeed(power);
                MR->setSpeed(power);
                delay(2000);
                if (redPosition == BOTH_RIGHT_BEFORE_DELIVERY && numB < 2)
                {
                    spin(LEFT);
                    direction = CLOCKWISE;
                }
                else
                {
                    spin(RIGHT);
                    direction = ANTICLOCKWISE;
                }
                if (complete2 == true)
                {
                    numB = 2;
                }
                _R = 0;
                location = LOOP;
                return FOLLOW_LINE;
            }
        }
    }
    else if (phase == 3)
    {
        // Deliver red blocks (location must be loop)
        if (redPosition == BOTH_RIGHT_BEFORE_DELIVERY)
        {
            // Move to get the first block and bring it to delivery target
            moveUntilBlock();
            grabBlock(true);
            spinToggleJunction();
            getUntilJunc(); // update untilJunc after passing T
            moveUntilJunction();
            releaseBlock();
            numR = 1;

            // Move back to get the other block
            spinToggleJunction();
            moveUntilJunction();
            skipJunc();
            moveUntilBlock();

            // Get the block and bring it to the other delivery target
            grabBlock(true);
            moveUntilJunction();
            releaseBlock();
            numR = 2;

            // Spin and move to phase 4
            return returnSpinToggleJunction();
        }
        else if (redPosition == BOTH_RIGHT)
        {
            // Place nearest red block on nearest red delivery
            moveUntilBlock();
            grabBlock(true);
            moveUntilJunction();
            releaseBlock();
            numR = 1;

            // Spin and move to other red block
            spinToggleJunction();
            moveUntilJunction();
            skipJunc(); // first T junction
            moveUntilJunction();
            skipJunc(); // second red delivery
            moveUntilBlock();

            // Grab block and deliver it
            grabBlock(true);
            spinToggleJunction();
            moveUntilJunction();
            skipJunc(); // skip delivery target
            followLineForwards(30);
            spinToggleJunction(); // spin around to orientate with target
            moveUntilJunction();
            releaseBlock();
            numR = 2;

            // Move to phase 4
            return returnSpinToggleJunction();
        }
        else if (redPosition == BOTH_LEFT)
        {
            // Spin and move to the other side of the junction
            spinToggleJunction();
            moveUntilJunction();
            skipJunc(); // skip T junction

            // Get first red block and deliver it
            moveUntilBlock();
            grabBlock(true);
            spinToggleJunction();
            moveUntilJunction();
            skipJunc(); // T junction
            moveUntilJunction();
            releaseBlock();
            numR = 1;

            // Get second block and deliver it
            spinToggleJunction();
            moveUntilJunction();
            skipJunc(); // T junction
            moveUntilBlock();
            grabBlock(true);
            moveUntilJunction();
            releaseBlock();
            numR = 2;

            // Move to phase 4
            return returnSpinToggleJunction();
        }
        else
        {
            return PANIC;
        }
    }
    else if (phase == 4)
    { // Return home
        // Get to T junction and turn into tunnel
        moveUntilJunction();
        skipJunc();
        turnIntoTunnel();
        location = TUNNEL;

        // Move through the tunnel
        moveUntilJunction();
        // Overshoot and turn left
        ML->setSpeed(power);
        MR->setSpeed(power);
        delay(5000);
        spin(LEFT);
        location = HOME;

        // Move to the home square and stop
        moveUntilJunction();
        MR->setSpeed(power);
        ML->setSpeed(power);
        delay(3500);
        return FINISH;
    } // End phase 4
    else if (phase == 5)
    { // Does something?

        return STOP; // End phase 5
    }
    else
    { // Lost!
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
    else if (start == 0 && numB == 2 && numR == 2)
    {
        phase = 4; //4th phase (return to start area)
    }
    else
    {
        phase = 5;
    }
}

output_status returnSpinToggleJunction()
{
    // Utility function when spinning in the loop
    // Toggle direction
    toggleDirection();
    // Update number until junction
    getUntilJunc();
    // spin the correct way
    if (direction == ANTICLOCKWISE)
    {
        return SPIN_R;
    }
    return SPIN_L;
}

void spinToggleJunction()
{
    // Utility function when spinning in the loop
    // Toggle direction
    toggleDirection();
    // Update number until junction
    getUntilJunc();
    // spin the correct way
    if (direction == ANTICLOCKWISE)
    {
        spin(RIGHT);
    }
    else
    {
        spin(LEFT);
    }
}

void grabBlock(bool moving)
{
    ML->setSpeed(0);
    MR->setSpeed(0);
    updateLights(moving);
    closeMechanism();
}

void releaseBlock()
{
    ML->setSpeed(0);
    MR->setSpeed(0);
    openMechanism();
    currentBlock = EMPTY;
    updateLights(true);
    ML->run(BACKWARD);
    MR->run(BACKWARD);
    ML->setSpeed(power);
    MR->setSpeed(power);
    delay(1000);
}

void moveUntilBlock()
{
    getAtblock();
    while (!atBlock)
    {
        lf4s();
        getAtblock();
    }
}

void moveUntilJunction()
{
    getAtJunction();
    while (!atJunction)
    {
        lf4s();
        getAtJunction();
    }
}

void followLineForwards(int iterations)
{
    for (int i = 0; i < iterations; i++)
    {
        lf4s();
    }
}

void turnIntoTunnel()
{
    // Overshoot the tunnel
    followLineForwards(15);
    // Turn into tunnel
    if (direction == CLOCKWISE)
    {
        ML-> run(BACKWARD);
        ML ->setSpeed(power);
        MR -> run(FORWARD);
        MR -> setSpeed(power);
        delay(1000);
        spin(LEFT);
    }
    else
    {
        ML-> run(FORWARD);
        ML ->setSpeed(power);
        MR -> run(BACKWARD);
        MR -> setSpeed(power);
        delay(1000);
        spin(RIGHT);
    }
    location = TUNNEL;
}