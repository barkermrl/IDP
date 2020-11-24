#include <Arduino.h>
#include <Adafruit_MotorShield.h>
#ifndef ELECTRONICS_H
#define ELECTRONICS_H

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
void detectBlock();
void detectBlockAhead();
void wait();

#endif