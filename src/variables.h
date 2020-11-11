#include <Arduino.h>
#include <Adafruit_MotorShield.h>

#ifndef VARIABLES_H
#define VARIABLES_H

extern const int ls1;
extern const int ls2; //Middle sensor
extern const int ls3;

extern int kp; //proportional coeff for control using running averages
extern int kw; //oscilatory coeff for control using single sensor. Higher kw causes higher oscilations

//Variables for the single sensor line follower:
extern int dir; //1 corresponds to left, -1 to right
extern bool change; //Whether or not the robot should change directions when hitting the black

//Variables for the 3 sensor line follower:
extern double avg1[10]; // last 10 inputs of the line sensors. The averages will be calculated from these functions
extern double avg2[10];
extern double avg3[10];

//Defining Motors:
extern Adafruit_MotorShield AFMS;
extern Adafruit_DCMotor *M2; //Left
extern Adafruit_DCMotor *M1; //Right

#endif