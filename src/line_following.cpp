#include <Arduino.h>
#include "electronics.h"
#include "spin.h"
#include "line_following.h"
#include "state.h"
#define turnThresh 200

// Control variables for pid loop
float Kp = 10; // For proportional control
float Ki = 10; // For integral control
float Kd = 5; // For derivative control
int derivative; // Derivative component of the correction
int integral; // Integral component of the correction
int error; // Error based on line sensor readings
int last_error; // Variable to store the previous error (for derivative)
int power_difference; // Term to correct the power

void pid()
{
    // Function to implement pid control for line following.
    // Largely based on the post here: https://medium.com/@TowardInfinity/pid-for-line-follower-11deb3a1a643
    // Note this could be adapted to use 4 line sensors if 2 doesn't do the job!
    // If 4 sensors are used, junction detection would have to pick up the two sensor readings
    // -i.e. R & RM would have to be on or L & LM would have to be on.

    // 1. Calculate error first based on the 2 central line sensors
    // Note error is positive when the robot is to the right of the line,
    // and negative when the robot is to the left of the line.

    // If the left or left middle sensor is on the line, robot is too far to the right.
    if (LOnLine()) {
        error = 2;
    }
    else if (LMOnLine()) {
        error = 1;
    }
    // If the right or right middle sensor is on the line, robot is too far to the left.
    else if (RMOnLine())
    {
        error = -1;
    }
    else if (ROnLine())
    {
        error = -2;
    }
    // If neither sensors are on the line, robot is directly on the line in the "dead zone".
    else {
        error = 0;
    }
    // (using the outer two sensors as well would give a greater rang of error for more stability)

    // 2. Calculate derivative of error based on the previous two readings.
    derivative = error - last_error;

    // 3. Calculate integral of error based on previous integral and current error.
    // Note this may require resetting to zero at some point to prevent accidental error accumulation.
    integral = integral + error;

    // 4. Calculate the power_difference correction (power difference is large if robot is too far to the right).
    power_difference = int(error*Kp + integral*Ki + derivative*Kd);

    // 5. Update speeds of the motors
    pidUpdateSpeed();

    // Print out for debugging
    Serial.print(int(error*Kp));
    Serial.print(' ');
    Serial.print(int(integral*Ki));
    Serial.print(' ');
    Serial.print(int(derivative*Kd));
    Serial.print(' ');
    Serial.println(power_difference);
}

void pidUpdateSpeed()
{
    // Function to update the speeds of the motors based on the power_difference calculated in pid loop.

    // Change left motor first
    // Max out the forward speed to 255
    if (power - power_difference > 255)
    {
        ML -> run(FORWARD);
        ML -> setSpeed(255);
    }
    // If correction is negative, reverse the motor direction
    else if (power - power_difference < 0)
    {
        ML -> run(BACKWARD);
        ML -> setSpeed(power_difference - power);
    }
    // Else correct the motor as normal
    else {
        ML -> run(FORWARD);
        ML -> setSpeed(power - power_difference);
    }

    // Now do the same thing for the right motor (opposite signs)
    if (power + power_difference > 255)
    {
        MR -> run(FORWARD);
        MR -> setSpeed(255);
    }
    // If correction is negative, reverse the motor direction
    else if (power + power_difference < 0)
    {
        MR -> run(BACKWARD);
        MR -> setSpeed(- power_difference - power);
    }
    // Else correct the motor as normal
    else {
        MR -> run(FORWARD);
        MR -> setSpeed(power + power_difference);
    }
}

void lf4s()
{
    // Line is 2cm wide, Targets are 7.5cm wide
    if (dir == R && (LMOnLine() /*or (kw > 150 && location != TUNNEL)*/ or (kw > 100 && location == TUNNEL)))
    {
        if (location == TUNNEL or location == BLUE_DELIVERY)
        {
            kw = 20;
        }
        else
        {
            kw = kw_min;
        }
        toggleDir();
        updateSpeed();
    }
    if (dir == L && (RMOnLine() /*or (kw > 150 && location != TUNNEL)*/ or (kw > 100 && location == TUNNEL)))
    {
        if (location == TUNNEL or location == BLUE_DELIVERY)
        {
            kw = 20;
        }
        else
        {
            kw = kw_min;
        }
        toggleDir();
        updateSpeed();
    }
    else
    {
        //followCurve();
        if (location == LOOP)
        {
            kw = kw + 0.5;
        }
        else if (location == HOME)
        {
            kw = kw + 0.7;
        }
        else if (location == TUNNEL)
        {
            kw = kw + 0.2;
        }
        else if (location == BLUE_DELIVERY)
        {
            kw = kw + 0.5;
        }
        if (kw > 250 && location != TUNNEL)
        {
            //Serial.print("off line");
        }
        updateSpeed();
        // Serial.println(kw);
    }
}

void toggleDir()
{
    //Serial.println("Toggle Direction");
    if (dir == L)
    {
        dir = R;
    }
    else if (dir = R)
    {
        dir = L;
    }
}

void skipJunc()
{
    if (atJunction && location == LOOP)
    {
        if (untilJunction == 2)
        {
            untilJunction = untilJunction - 1;
            if (direction == ANTICLOCKWISE)
            {
                MR->setSpeed(power);
                ML->setSpeed(power);
                while (atJunction)
                {
                    getAtJunction();
                }
                delay(2000);
                spin(LEFT);
                lf4s();
            }
            else
            {
                MR->setSpeed(power);
                ML->setSpeed(power);
                while (atJunction)
                {
                    getAtJunction();
                }
                lf4s();
            }
        }
        else if (untilJunction == 1)
        {
            untilJunction = untilJunction - 1;
            if (direction == ANTICLOCKWISE)
            {
                MR->setSpeed(power);
                ML->setSpeed(power);
                while (atJunction)
                {
                    getAtJunction();
                }
                lf4s();
            }
            else if (direction == CLOCKWISE)
            {
                MR->setSpeed(power);
                ML->setSpeed(power);
                while (atJunction)
                {
                    getAtJunction();
                }
                delay(2000);
                spin(RIGHT);
                lf4s();
            }
        }
        else if (untilJunction == 0)
        {
            MR->setSpeed(power);
            ML->setSpeed(power);
            while (atJunction)
            {
                getAtJunction();
            }
            lf4s();
            untilJunction = 2;
        }
    }
}