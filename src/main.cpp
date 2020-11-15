#include <Arduino.h>
#include "line_following.h" // line following algorithms
#include "spin.h"           // algorithms to spin 90 and 180
#include "state.h"          // algorithms to get state variables
#include "variables.h"      // contains global variables
#include "electronics.h"    // contains electronics interface
#include "decision.h"       // decides what to do at each timestep

// General global variables
double kw = 10; //oscilatory coeff for control using single sensor. Higher kw causes higher oscilations
const int kw_min = kw;
int kp = 10;     //proportional coeff for control using running averages
int power = 100; //average speed of motors

// Variables for the single sensor line follower:
bool change = true; //Whether or not the robot should change directions when hitting the black
bool junc = false;  //Whether the robot is at a junction (LEGACY)

// Variables for 4 sensor line follower:
int dir = 1; //1 corresponds to left, -1 to right

// Defining state variables (note these are not global!)
int numB = 0;            //number of blue targets delivered
int numR = 0;            //number of red targets delivered
int tunnelSide = 0;      //which side of the tunnel are we currently
int untilJunction = 0;   //number of "junction detections" until we actually hit a junction
bool atJunction = false; //currently not at a junction
int currentBlock = 0;    //2 for blue 1 for red 0 for empty
int direction = 0;       //1 for AC 2 for C.
int output = 0;          //determines what the robot does at each timestep

// enum output_status
// {
//     NOT_DEPLOYED = 0,
//     DEPLOYED = 1,
//     LOST = 2
// };

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
    // Get state variables for this timestep
    numB = getNumB();
    numR = getNumR();
    tunnelSide = getTunnelSide();
    untilJunction = getUntilJunc();
    atJunction = getAtJunction();
    currentBlock = getCurrentBlock();
    direction = getDirection();
    
    pauseButton();
}