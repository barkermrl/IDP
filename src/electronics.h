//Defining Motors:
#include <Adafruit_MotorShield.h>
#ifndef ELECTRONICS_H
#define ELECTRONICS_H

extern Adafruit_MotorShield AFMS;
extern Adafruit_DCMotor *ML; //Left
extern Adafruit_DCMotor *MR; //Right

void electronics_setup();
bool leftOnLine();
bool centerOnLine();
bool rightOnLine();

#endif