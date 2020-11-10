#include <Arduino.h>
#include <Adafruit_MotorShield.h>
#define ls1 6
#define ls2 7 //Middle sensor
#define ls3 8
#define kp 50 //proportional coeff for control using running averages
#define kw 10 //oscilatory coeff for control using single sensor. Higher kw causes higher oscilations

//Variables for the single sensor line follower:
int dir = 1; //1 corresponds to left, -1 to right
bool change = true; //Whether or not the robot should change directions when hitting the black

//Variables for the 3 sensor line follower:
double avg1[10] = {1,1,1,1,1,1,1,1,1,1}; // last 10 inputs of the line sensors. The averages will be calculated from these functions
double avg2[10] = {0,0,0,0,0,0,0,0,0,0};
double avg3[10] = {1,1,1,1,1,1,1,1,1,1};

//Defining Motors:
Adafruit_MotorShield AFMS = Adafruit_MotorShield();
Adafruit_DCMotor *M2 = AFMS.getMotor(2); //Left
Adafruit_DCMotor *M1 = AFMS.getMotor(1); //Right