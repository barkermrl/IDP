#include <Arduino.h>
#include <Adafruit_MotorShield.h>
#ifndef ELECTRONICS_H
#define ELECTRONICS_H

//Defining Motors:
extern Adafruit_MotorShield AFMS;
extern Adafruit_DCMotor *ML; //Left
extern Adafruit_DCMotor *MR; //Right

void electronics_setup();
int lrangeDistance();
int srangeDistance();
void pauseButton();
bool LOnLine();
bool LMOnLine();
bool RMOnLine();
bool ROnLine();
void updateSpeed();

#endif