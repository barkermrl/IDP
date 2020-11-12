#include <Arduino.h>
#include "lf1s.h"
#include "spin_180.h"
#include "variables.h"
#include "electronics.h"

int kp = 50;     //proportional coeff for control using running averages
int kw = 50;     //oscilatory coeff for control using single sensor. Higher kw causes higher oscilations
int power = 100; // average speed of motors

//Variables for the single sensor line follower:
int dir = 1;         //1 corresponds to left, -1 to right
bool change = false; //Whether or not the robot should change directions when hitting the black

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

    MR->setSpeed(power);
    ML->setSpeed(power);

    electronics_setup();
}

void loop()
{
    spin_180();
    while (true)
    {
        lf1s();
        // if interrupt is pressed, set motor speed to 0
        if (pauseButton())
        {
            MR->setSpeed(0);
            ML->setSpeed(0);
        }
    }
}