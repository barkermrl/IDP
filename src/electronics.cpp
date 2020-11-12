#include <Arduino.h>
#include <Adafruit_MotorShield.h>
#include "variables.h"
#include "electronics.h"

// Variables for sensors
#define lsl 6 //Left sensor
#define lsm 7 //Middle sensor
#define lsr 6 //Right sensor
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
    pinMode(lsl, INPUT); //left
    pinMode(lsm, INPUT); //centre
    pinMode(lsr, INPUT); //right
    pinMode(interruptPin, INPUT_PULLUP);

    pinMode(LED_BUILTIN, OUTPUT); //builtin LED
}

bool leftOnLine() {
    return (digitalRead(lsl) == HIGH);
}

bool centerOnLine() {
    return (digitalRead(lsm) == HIGH);
}

bool rightOnLine() {
    return (digitalRead(lsr) == HIGH);
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