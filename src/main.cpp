#include <Arduino.h>
#include <Wire.h>
#include "lf3s.h"
#include "lf1s.h"
#include "spin_180.h"
#include "variables.h"

// Variables for sensors
const int ls1 = 6;
const int ls2 = 7; //Middle sensor
const int ls3 = 8;
int kp = 50; //proportional coeff for control using running averages
int kw = 10; //oscilatory coeff for control using single sensor. Higher kw causes higher oscilations

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

void setup()
{
    Serial.begin(9600); // set up Serial library at 9600 bps
    Serial.println("Autobots, transform and roll out!");
    AFMS.begin(); // create with the default frequency 1.6KHz

    pinMode(ls1, INPUT); //left
    pinMode(ls2, INPUT); //centre
    pinMode(ls3, INPUT); //right

    pinMode(LED_BUILTIN, OUTPUT); //builtin LED

    M1->run(FORWARD);
    M2->run(FORWARD);
}

void loop()
{
    lf3s();
    lf1s();
    spin_180();
}