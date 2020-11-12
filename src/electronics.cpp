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

//Defining Motors:
Adafruit_MotorShield AFMS = Adafruit_MotorShield();
Adafruit_DCMotor *ML = AFMS.getMotor(2); //Left
Adafruit_DCMotor *MR = AFMS.getMotor(1); //Right

void electronics_setup()
{
    pinMode(lsl, INPUT); //left
    pinMode(lsm, INPUT); //centre
    pinMode(lsr, INPUT); //right

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

int lrangeDistance() {
    return analogRead(lrange);
}

int srangeDistance() {
    return analogRead(srange);
}