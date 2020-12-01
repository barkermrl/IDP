#include <Arduino.h>
#include "electronics.h"
#include "line_following.h"
#include "state.h"
#include "output.h"

void spin(spin_direction_status spin_direction) //direction tells you wether or not you should spin to the right (-1) or to the left (+1)
{
    //Function to do a 180* turn (Assuming midde sensor comes off the line during the turn)
    if (spin_direction == LEFT)
    { //spinning to the left
        MR->run(FORWARD);
        ML->run(BACKWARD);
        ML->setSpeed(power);
        MR->setSpeed(power);
        Serial.println("Started Spinning Left");
    }
    else //spinning to the right
    {
        MR->run(BACKWARD);
        ML->run(FORWARD);
        ML->setSpeed(power);
        MR->setSpeed(power);
    }

    if (!(RMOnLine() or LMOnLine()) && location == LOOP) // off the line and in loop
    {
        delay(500);
    }

    while (RMOnLine() or LMOnLine()) // now on line
    {
        delay(500);
    }

    while (true)
    {
        if (RMOnLine() && spin_direction == LEFT)
        {
            MR->run(FORWARD);
            ML->run(FORWARD);
            ML->setSpeed(0);
            MR->setSpeed(0);

            // dir = L;
            // for (int i = 0; i<1000; i++){
            //     lf4s_dummy();
            // }
            break;
        }
        if (LMOnLine() && spin_direction == RIGHT)
        {
            MR->run(FORWARD);
            ML->run(FORWARD);
            ML->setSpeed(0);
            MR->setSpeed(0);
            // dir = R;
            // for (int i = 0; i<1000; i++){
            //     lf4s_dummy();
            // }
            break;
        }
    }
    resetID();
}

void reverse(int time)
{
    ML->run(BACKWARD);
    MR->run(BACKWARD);
    ML->setSpeed(power);
    MR->setSpeed(power);
    delay(time);
    ML->run(FORWARD);
    MR->run(FORWARD);
    ML->setSpeed(0);
    MR->setSpeed(0);
}

void deliverBlue2()
{
    // Overshoot BLue area T junction.
    ML->setSpeed(power); 
    MR->setSpeed(power);
    delay(2000);
    // Spin left to correct bearing.
    spin(LEFT);
    // Spin Left a bit more to line up block
    MR->run(FORWARD);
    ML->run(BACKWARD);
    ML->setSpeed(power);
    MR->setSpeed(power);
    delay(150);
    ML->setSpeed(0);
    MR->setSpeed(0);
    reverse(400);
    ML->setSpeed(0);
    MR->setSpeed(0);
    currentBlock = EMPTY;
    updateLights(false);
    openMechanism();
    numB = 1;
    delay(2000);
    updateLights(true);
    // Reverse back out
    reverse(1000);
    // Spin left
    spin(LEFT);
    ML->setSpeed(power);
    MR->setSpeed(power);
    delay(2000);
    spin(LEFT);

}

void deliverBlue1()
{   
    //overshoot BLue area T junction
    ML->setSpeed(power); 
    MR->setSpeed(power);
    delay(2000);
    //Spin left
    spin(LEFT);    
    //overshoot first target      
    ML->setSpeed(power); 
    MR->setSpeed(power);
    delay(2000);
    //spin right onto straight to second target
    spin(RIGHT);
    // Keep going until you hit the junction
    getAtJunction();
    while (!atJunction)
    {
        lf4s(false);
        getAtJunction();
    }
    //stop and drop the block
    ML->setSpeed(0);
    MR->setSpeed(0);
    currentBlock = EMPTY;
    updateLights(false);
    openMechanism();
    numB = 1;
    delay(2000);
    updateLights(true);
    // reverse back out
    ML->run(BACKWARD);
    MR->run(BACKWARD);
    ML->setSpeed(power); //to move away from block
    MR->setSpeed(power);
    delay(1000);
    ML->setSpeed(150);
    MR->setSpeed(70);
    delay(3000);
    spin(LEFT);
}
