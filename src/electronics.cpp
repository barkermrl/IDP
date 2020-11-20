#include <Arduino.h>
#include <Adafruit_MotorShield.h>
#include "electronics.h"
#include "line_following.h"
#include "state.h"
#include <Servo.h>

// Variables for sensors
#define ls1 6    //L
#define ls2 7    //Middle sensor for single line following, LM for 4 sensor following
#define ls3 5    //RM
#define ls4 4    //R

#define colour1 0 //colour sensor 1
#define colour2 1 //colour sensor 2
#define ambLightSensor 3 //Ambient light sensor 

#define srange 2 // Long range sensor
#define lrange A0 // Short range sensor

// Defining interrupt
#define interruptPin 13

#define LEDblue 10
#define LEDoragne 11
#define LEDred 12

#define servopin 9 // Servo pin

bool paused = false;

//Defining Motors:
Servo myservo;
Adafruit_MotorShield AFMS = Adafruit_MotorShield();
Adafruit_DCMotor *ML = AFMS.getMotor(2); //Left
Adafruit_DCMotor *MR = AFMS.getMotor(1); //Right

void electronics_setup()
{
    pinMode(interruptPin, INPUT_PULLUP);

    pinMode(ls1, INPUT);          //L
    pinMode(ls2, INPUT);          //LM
    pinMode(ls3, INPUT);          //RM
    pinMode(ls4, INPUT);          //R
    pinMode(LED_BUILTIN, OUTPUT); //builtin LED

    myservo.attach(servopin);
}

bool LOnLine()
{
    return (digitalRead(ls1) == HIGH);
}

bool LMOnLine()
{
    return (digitalRead(ls2) == HIGH);
}

bool RMOnLine()
{
    return (digitalRead(ls3) == HIGH);
}
bool ROnLine()
{
    return (digitalRead(ls4) == HIGH);
}

void updateSpeed()
{
    //Serial.println("Update speed");
    if ((power - kw * dir) > 255)
    {
        ML->setSpeed(255);
    }
    else if ((power - kw * dir) < 0)
    {   
        //ML -> run(BACKWARD);
        //ML->setSpeed(abs(power - kw * dir));
        ML -> setSpeed(0);
    }
    else
    {
        ML->setSpeed(floor(power - kw * dir));
    }

    if ((power + kw * dir) > 255)
    {
        MR->setSpeed(255);
    }
    else if ((power + kw * dir) < 0)
    {
        // MR -> run(BACKWARD);
        // MR->setSpeed(abs(power + kw * dir));
        MR -> setSpeed(0);
    }
    else
    {
        MR->setSpeed(floor(power + kw * dir));
    }
}

void pauseButton()
{
    // if button is pressed
    if (!digitalRead(interruptPin))
    {
        // turn the motors off
        MR->setSpeed(0);
        ML->setSpeed(0);
        // wait until button is released
        while (!digitalRead(interruptPin))
        {
        };
        // wait while button is off
        while (digitalRead(interruptPin))
        {
        };
        // wait until button has been released
        while (!digitalRead(interruptPin))
        {
        };
        // return to main control flow
    }
}

float lrangeDistance()
{
    // long range distance reading
    // returns an integer giving the distance reading in mm

    /***********************
    TODO
    ***********************/

    return analogRead(lrange);
}

float srangeDistance()
{
    // short range distance reading
    // returns an integer giving the distance reading in mm
    float distance;
    distance = -4.9261 + 33.4525 / (float(analogRead(srange) * 5) / 1024);
    return distance;
}

void openMechanism()
{
    // Opens mechanism
    myservo.write(0);
}

void closeMechanism()
{
    // Opens mechanism
    myservo.write(70);
}
