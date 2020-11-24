#ifndef ELECTRONICS_H
#define ELECTRONICS_H

#include <Arduino.h>
#include <Adafruit_MotorShield.h>

//Defining Motors:
extern Adafruit_MotorShield AFMS;
extern Adafruit_DCMotor *ML; //Left
extern Adafruit_DCMotor *MR; //Right

void electronics_setup();
float irDistance();
void pauseButton();
bool LOnLine();
bool LMOnLine();
bool RMOnLine();
bool ROnLine();
void updateSpeed();
void openMechanism();
void closeMechanism();
bool colour1read();
bool amblight();
void wait();
void getAtblock();
void getBlockAhead();
void updateLights(bool moving);

#endif