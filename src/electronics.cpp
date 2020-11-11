#include <Arduino.h>
#include <Adafruit_MotorShield.h>
#include "variables.h"
#include "electronics.h"

// Variables for sensors
#define ls1 6 //Left sensor
#define ls2 7 //Middle sensor
#define ls3 8 //Right sensor

//Defining Motors:
Adafruit_MotorShield AFMS = Adafruit_MotorShield();
Adafruit_DCMotor *ML = AFMS.getMotor(2); //Left
Adafruit_DCMotor *MR = AFMS.getMotor(1); //Right

void electronics_setup()
{
    pinMode(ls1, INPUT); //left
    pinMode(ls2, INPUT); //centre
    pinMode(ls3, INPUT); //right

    pinMode(LED_BUILTIN, OUTPUT); //builtin LED
}

bool leftOnLine() {
    return (digitalRead(ls1) == LOW);
}

bool centerOnLine() {
    return (digitalRead(ls2) == LOW);
}

bool rightOnLine() {
    return (digitalRead(ls3) == LOW);
}