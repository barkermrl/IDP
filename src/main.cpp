#include <Arduino.h>
#include "line_following.h" // line following algorithms
#include "output.h"           // algorithms to spin 90 and 180
#include "state.h"          // algorithms to get state variables
#include "electronics.h"    // contains electronics interface
#include "decision.h"       // decides what to do at each timestep
#include <Servo.h>

// General variables controlling robot behaviour
double kw = 0;         //oscilatory coeff for control using single sensor. Higher kw causes higher oscilations
const int kw_min = kw; //set kw_min to kw for development
int power = 120;       //average speed of motors

// Variables for 4 sensor line follower:
dir_status dir = L; //1 corresponds to left, -1 to right

// Defining state variables
int numB = 0; //number of blue targets delivered
int numR = 0; //number of red targets delivered


bool atJunction = false; //currently at a junction

int phase = 0;           //the phase we are currently in
int _R = 0;              //(phase 2) 0 means spin when you see a red block and 1 means move it
bool atBlock = false;    // 0 for no block detected, 1 for block detected by proximity
bool blockAhead = false; // Block detected by IR
bool complete2 = false;  // Completed second phase
bool hitRED = false;

int start = 1;           //a variable that calls for the start/end sequence (SET TO 1 FOR START)
int untilJunction = 0;   //number of "junction detections" until we actually hit a junction (SET TO 0 FOR START UP)
location_status location = HOME;          //Which section of the track we're in (SET TO HOME FOR START UP)
direction_status direction = NONE;   //-1 for AC 1 for C. (SET TO NONE FOR START UP)


currentBlock_status currentBlock = EMPTY; //Colour of block in grabber (or EMPTY FOR START UP)

output_status output;                     //Determines what the robot does at each timestep
redPosition_status redPosition = UNKNOWN;  // Position of red blocks to start
sequence1 seq1 = NA1;
sequence2 seq2 = NA2;

void setup()
{
    Serial.begin(9600); // set up Serial library at 9600 bps
    Serial.println("autoBLOCKS, transform and roll out!");
    AFMS.begin(); // create with the default frequency 1.6KHz

    MR->run(FORWARD);
    ML->run(FORWARD);

    // Update electronics
    electronics_setup();
    // Wait until button is pressed
    wait();
    Serial.println("Stop waiting");
    // Set speed of motors to initial value
    // updateSpeed();
}

void loop()
{
    // Get state variables for this timestep
    getPhase();
    getAtblock();
    getAtJunction();
    // Get output from the decision making process
     output = makeDecision();
    // Switch case to call the correct output
    // output = TEST;
    if (output == FOLLOW_LINE)
    {
        lf4s(true);
        updateLights(true);
    }
    else if (output == SPIN_L)
    {
        spin(LEFT);
        lf4s(true);
    }
    else if (output == SPIN_R)
    {
        spin(RIGHT);
        lf4s(true);
    }
    else if (output == STOP)
    {
        ML->setSpeed(0);
        MR->setSpeed(0);
        updateLights(false);
        //Serial.println("STOP");
    }
    else if (output == FINISH)
    {
        ML->setSpeed(0);
        MR->setSpeed(0);
        updateLights(false);
        // Get stuck in infinite while loop
        while (true)
        {
            //  Serial.println("WHILE");
        }
    }
    else if (output == TEST)
    {
        closeMechanism();
        delay(1000);
        moveUntilJunction();
        deliverBlue2();
        while (true) {};
    }
    else
    {
        // By default continue following the line
        lf4s(true);
        updateLights(true);

    }
}