#include <Arduino.h>
#include "line_following.h" // line following algorithms
#include "spin.h"           // algorithms to spin 90 and 180
#include "state.h"          // algorithms to get state variables
#include "electronics.h"    // contains electronics interface
#include "decision.h"       // decides what to do at each timestep

// General variables controlling robot behaviour
double kw = 10;        //oscilatory coeff for control using single sensor. Higher kw causes higher oscilations
const int kw_min = kw; //set kw_min to kw for development
int kp = 10;           //proportional coeff for control using running averages
int power = 100;       //average speed of motors

// Variables for the single sensor line follower:
bool change = true; //Whether or not the robot should change directions when hitting the black
bool junc = false;  //Whether the robot is at a junction (LEGACY)

// Variables for 4 sensor line follower:
int dir = 1; //1 corresponds to left, -1 to right

// Defining state variables
int numB = 0;            //number of blue targets delivered
int numR = 0;            //number of red targets delivered
location_status location = HOME;        //where we are
int untilJunction = 0;   //number of "junction detections" until we actually hit a junction
bool atJunction = false; //currently not at a junction
int currentBlock = 0;    //2 for blue 1 for red 0 for empty
int direction = 0;       //-1 for AC 1 for C.
int directionSPIN = 1;   // if spin, which direction? -1 right 1 left
output_status output;    //determines what the robot does at each timestep
int start = 1;           //a variable that calls for the start/end sequence
int phase = 0;           //the phase we are currently in

void setup()
{
    Serial.begin(9600); // set up Serial library at 9600 bps
    Serial.println("autoBLOCKS, transform and roll out!");
    AFMS.begin(); // create with the default frequency 1.6KHz

    MR->run(FORWARD);
    ML->run(FORWARD);

    electronics_setup();
    delay(5000);
    updateSpeed();
}

void loop()
{
    // Get state variables for this timestep
    // numB = getNumB();
    // numR = getNumR();
    // tunnelSide = getTunnelSide();
    // untilJunction = getUntilJunc();
    // atJunction = getAtJunction();
    // currentBlock = getCurrentBlock();
    // direction = getDirection();
    getPhase();
    getAtJunction();

    // Get output from the decision making process
    output = makeDecision();

    // Switch case to call the correct output
    switch (output)
    {
    case SPIN_L:
        spin(LEFT);
        lf4s();
        break;

    case STOP:
        ML->setSpeed(0);
        MR->setSpeed(0);
        break;

    default:
        // By default continue following the line
        lf4s();
        break;
    }

    // Check the interrupt
    pauseButton();
}