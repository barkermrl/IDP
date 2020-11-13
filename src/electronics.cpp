#include <Arduino.h>
#include <Adafruit_MotorShield.h>
#include "variables.h"
#include "electronics.h"

// Variables for sensors
#define ls1 9 //L
#define ls2 6 //Middle sensor for single line following, LM for 4 sensor following
#define ls3 7 //RM
#define ls4 8 //R
#define srange A0 // Long range sensor
#define lrange A1 // Short range sensor

// Defining interrupt
#define interruptPin 13
bool paused = false;

//Defining Motors:
Adafruit_MotorShield AFMS = Adafruit_MotorShield();
Adafruit_DCMotor *ML = AFMS.getMotor(2); //Left
Adafruit_DCMotor *MR = AFMS.getMotor(1); //Right


void electronics_setup()
{
    pinMode(interruptPin, INPUT_PULLUP);

    pinMode(ls1, INPUT); //L
    pinMode(ls2, INPUT); //LM
    pinMode(ls3, INPUT); //RM
    pinMode(ls4, INPUT); //R
    pinMode(LED_BUILTIN, OUTPUT); //builtin LED
}

bool LOnLine() {
    return (digitalRead(ls1) == HIGH);
}

bool LMOnLine() {
    return (digitalRead(ls2) == HIGH);
}

bool RMOnLine() {
    return (digitalRead(ls3) == HIGH);
}
bool ROnLine(){
    return (digitalRead(ls4) == HIGH);
}

void updateSpeed(){
    if ((power - kw*dir)> 255){
        ML -> setSpeed(255);
    }
    else if ((power - kw*dir)< 0)
    {
        ML -> setSpeed(0);
    }
    else{
        ML -> setSpeed(floor(power - kw*dir));
    }

    if ((power + kw*dir)> 255){
        MR -> setSpeed(255);
    }
    else if ((power + kw*dir)< 0)
    {
        MR -> setSpeed(0);
    }
    else
    {
        MR -> setSpeed(floor(power + kw*dir));
    }   
}

bool pauseButton() {
    if (!digitalRead(interruptPin)) {
        // delay to allow time for button to reset
    while(!digitalRead(interruptPin));
        // toggle paused boolean
        paused = !paused;
        delay(10); 
    }
    return paused;
}

int lrangeDistance() {
    // long range distance reading
    // returns an integer giving the distance reading in mm
    return analogRead(lrange);
}

int srangeDistance() {
    // short range distance reading
    // returns an integer giving the distance reading in mm
    return analogRead(srange);
}