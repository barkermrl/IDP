#include <Arduino.h>
#include "lf1s.h"
#include "spin_180.h"
#include "variables.h"
#include "electronics.h"
#include "lf4.h"
#include "juntTest.h"

double kw = 10;//oscilatory coeff for control using single sensor. Higher kw causes higher oscilations
const int kw_min = kw; 
int kp = 10; //proportional coeff for control using running averages
int power = 100; // average speed of motors

//Variables for the single sensor line follower:
int dir = 1; //1 corresponds to left, -1 to right
bool change = true; //Whether or not the robot should change directions when hitting the black
bool junc = false;

//Variables for the 3 sensor line follower:
double avg1[10] = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1}; // last 10 inputs of the line sensors. The averages will be calculated from these functions
double avg2[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
double avg3[10] = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1};

void setup()
{
    Serial.begin(9600); // set up Serial library at 9600 bps
    Serial.println("Autobots, transform and roll out!");
    AFMS.begin(); // create with the default frequency 1.6KHz

    MR->run(FORWARD);
    ML->run(FORWARD);

    electronics_setup();
    updateSpeed();
}

void loop()
{
    if (junc == false){
        //lf3s();
        // lf1s();
        // spin_180();
        lf4();
        juncTest();
    }
    if (junc == true){
        MR -> setSpeed(power);
        ML -> setSpeed(power);
        delay(500);
        spin_180();
        junc = false;
    }
    pauseButton();
}