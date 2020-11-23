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
        if (location == LOOP && currentBlock == EMPTY && !atBlock)
        {
            if (!atJunction) //if you are not at a junction and do not have a block
            {
                return FOLLOW_LINE; //Follow line
            }
            if (atJunction) //if you are at a junction, skip it
            {
                skipJunc(); //function to determine the best way to skip a junction based on your position
                return FOLLOW_LINE;
            }
        }

        else if (location == LOOP && currentBlock == EMPTY && atBlock) //detected block so decide wether or not to pick up based on colour and _R
        {
            //PICK UP BLOCK and IDENTIFY
            closeMechanism(); //Pick up block
            if (colour1read() == 0) //if its blue
            {
                currentBlock == BLUE; 
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
                untilJunction = 2 - untilJunction; 
            }
            else if (colour1read() == 1 && _R == 0) //if its red and you havent already hit a red block
            {
                openMechanism(); //release the block
                _R == 1; //to pick up and move the next red block we hit
                ML->run(BACKWARD);
                MR->run(BACKWARD);
                ML->setSpeed(power);
                MR->setSpeed(power);
                delay(3000);  //make sure block it outside the arms
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
            else if (colour1read() == 1 && _R == 1) //if the block is red and you already encountered a red block
            {
                currentBlock == RED; //pick it up
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

        else if (location == LOOP && currentBlock == RED && !blockAhead) //if you have a red block, keep going untill u hit another block
        {
            if (!atJunction) 
            {
                return FOLLOW_LINE;
            }
            else //if you hit a junction, skip it
            {
                skipJunc();
            }
        }

        else if (location == LOOP && currentBlock == RED && blockAhead) //if you have a read block and there is a block ahead (lrange sensor) 
        {
            ML->run(BACKWARD);//go back to leave space between the blocks
            MR->run(BACKWARD);
            ML->setSpeed(power);
            MR->setSpeed(power);
            delay(1000);
            openMechanism();//release the red block
            delay(2000);//reverse to let the block out of the area of the mechanism
            if (direction == CLOCKWISE)//spin
            {
                spin(RIGHT);
                direction = ANTICLOCKWISE;
            }
            else//spin
            {
                spin(LEFT);
                direction = CLOCKWISE;
            }
            untilJunction = 2 - untilJunction;
            currentBlock = EMPTY;
            return FOLLOW_LINE;
        }

        else if (location == LOOP && currentBlock == BLUE) //Have the blue block, look for the junction and take it
        {
            if (!atJunction)
            {
                return FOLLOW_LINE;
            }
            else if (atJunction && untilJunction == 0) //if you are at the junction
            {
                ML->setSpeed(power);
                MR->setSpeed(power);
                delay(2000); //pass it slightly to make spinning better
                if (direction == ANTICLOCKWISE) //spin into tunel
                {
                    spin(RIGHT);
                    return FOLLOW_LINE;
                }
                else //spin into tunnel
                {
                    spin(LEFT);
                    return FOLLOW_LINE;
                }
                location = TUNNEL;
                direction = NONE;
            }
            else if (atJunction && untilJunction != 0) //if you drive over a red target, skip it
            {
                skipJunc();
                return FOLLOW_LINE;
            }
        }

        else if (location == TUNNEL && currentBlock == BLUE) //have a blue block and going through the tunnel
        {
            if (!atJunction)
            {
                return FOLLOW_LINE;
            }
            else //hit the curved junction
            {
                ML->setSpeed(power);
                MR->setSpeed(power);
                delay(2000);// skip it then...
                spin(RIGHT);//...spin right
                location = BLUE_DELIVERY;//set location to delivery area
                if (numB == 0) //depending on how many blocks we have delivered, set the delivery target
                {
                    untilJunction = 2; //deep target
                }
                else if (numB == 1) //set delivery target
                {
                    untilJunction = 1;//shallow target
                }
                return FOLLOW_LINE;
            }
        }

        else if (location == BLUE_DELIVERY && currentBlock == BLUE) //once you are in the delivery area with a blue block...
        {
            if (!atJunction)
            {
                return FOLLOW_LINE;
            }
            if (atJunction && direction == NONE) //not in the loop yet (T junction) 
            {
                ML->run(FORWARD);
                MR->run(FORWARD);
                ML->setSpeed(power);
                MR->setSpeed(power);
                delay(2000); //go a little forward to imporve spin
                spin(LEFT); //always spin left
                direction = CLOCKWISE;
                untilJunction = untilJunction - 1; //reduce untill junction by 1
            }
            else if (atJunction && untilJunction == 1 && direction == CLOCKWISE) //if we hit th first "junction" (target) and it is not the target
            {
                ML->run(FORWARD);
                MR->run(FORWARD);
                ML->setSpeed(power);
                MR->setSpeed(power);
                delay(2000); //skip it and 
                spin(RIGHT);//spin right 
                untilJunction = untilJunction - 1;
            }
            else if (atJunction && untilJunction == 0)//if we hit the target junction, drop target
            {
                if (numB == 0) // if we have not delivered any targets before (@ deep target)
                {
                    ML->setSpeed(0);
                    MR->setSpeed(0);
                    openMechanism(); //release block and update state variables
                    currentBlock = EMPTY;
                    numB = numB + 1;
                    ML->run(BACKWARD);
                    MR->run(BACKWARD);
                    ML->setSpeed(power);
                    MR->setSpeed(power);
                    delay(3000);
                    spin(RIGHT); //spin directly onto area before junction
                    direction = NONE;
                    untilJunction = 1;
                    return FOLLOW_LINE;
                }
                if (numB == 1) //if it is the shallow target, spin and adjust
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

        else if (location == BLUE_DELIVERY && currentBlock == EMPTY) //heading back to loop
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
        // location must be loop
        if (numR == 0)
        {
            // If we're at a junction, update count.
            if (atJunction)
            {
                getUntilJunc();
            }
            // If there is a block ahead...
            if (blockAhead)
            {
                // ... and we don't one, pick it up.
                if (currentBlock == EMPTY)
                {
                    currentBlock = RED;
                    return GRAB_BLOCK;
                }
                // ... and we do have one, spin around.
                else if (currentBlock == RED)
                {
                    return spinToggleJunction();
                }
            }
            // If we don't have a block, continue line following.
            else
            {
                return FOLLOW_LINE;
            }
        }
        else if (numR == 1)
        {
            // If we have a block...
            if (currentBlock == RED) {
                // ...and there's a block ahead, spin around.
                if (blockAhead) {
                    return spinToggleJunction();
                }
                // ... and we're at a delivery target, release block.
                else if (atJunction && untilJunction != 0){
                    // Update number of blocks delivered
                    numR = 2;
                    return RELEASE_BLOCK;
                }
                // ... and we're at the tunnel junction, keep going.
                else if (atJunction && untilJunction == 0)
                {
                    // Update untilJunction
                    getUntilJunc();
                    return FOLLOW_LINE;
                }
                // ...and nothing is ahead, keep going.
                else {
                    return FOLLOW_LINE;
                }
            }
            // If we don't have a block...
            else {
                // ... and there's a block ahead, pick it up.
                if (blockAhead) {
                    return GRAB_BLOCK;
                }
                // ... and there's a junction, update and continue.
                else if (atJunction) {
                    getUntilJunc();
                    return FOLLOW_LINE;
                }
                // ... and there's nothing, continue.
                else {
                    return FOLLOW_LINE;
                }
            }
        }
        else if (numR == 2)
        {
            // Set phase to 4 and spin around.
            phase = 4;
            return spinToggleJunction();
        }

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
                    return spinToggleJunction();
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

output_status spinToggleJunction()
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