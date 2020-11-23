#include <Arduino.h>
#include "line_following.h" // line following algorithms
#include "spin.h"           // algorithms to spin 90 and 180
#include "state.h"          // algorithms to get state variables
#include "electronics.h"    // contains electronics interface
#include "decision.h"       // decides what to do at each timestep
#include <Servo.h>

// General variables controlling robot behaviour
double kw = 20;        //oscilatory coeff for control using single sensor. Higher kw causes higher oscilations
const int kw_min = kw; //set kw_min to kw for development
int kp = 10;           //proportional coeff for control using running averages
int power = 100;       //average speed of motors

// Variables for the single sensor line follower:
bool change = true; //Whether or not the robot should change directions when hitting the black
bool junc = false;  //Whether the robot is at a junction (LEGACY)

// Variables for 4 sensor line follower:
dir_status dir = L; //1 corresponds to left, -1 to right

// Defining state variables
int numB = 0; //number of blue targets delivered
int numR = 0; //number of red targets delivered

int untilJunction = 0;   //number of "junction detections" until we actually hit a junction
bool atJunction = false; //currently not at a junction
bool blockAhead = false; //if there is a block ahead
int start = 1;           //a variable that calls for the start/end sequence
int phase = 0;           //the phase we are currently in
int counter = 0;
int turning = 0;

int test = 0;

currentBlock_status currentBlock = EMPTY; //Colour of block in grabber (or EMPTY)
location_status location = HOME;          //Which section of the track we're in
direction_status direction = NONE;   //-1 for AC 1 for C.
output_status output;                     //Determines what the robot does at each timestep

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
    //getPhase();
    //getBlockAhead();

    if (turning == 0)
    {
        getAtJunction();
    }

    // Get output from the decision making process
    //output = makeDecision();
    counter++;
    output = FOLLOW_LINE;
    // Switch case to call the correct output
    switch (output)
    {
    case SPIN_L:
        spin(LEFT);
        lf4s();
        Serial.println("Done Spin");
        break;

    case SPIN_R:
        spin(RIGHT);
        lf4s();
        break;

    case STOP:
        ML->setSpeed(0);
        MR->setSpeed(0);
        //Serial.println("STOP");
        break;

    case FINISH:
        ML->setSpeed(0);
        MR->setSpeed(0);
        // Get stuck in infinite while loop
        while (true)
        {
            //  Serial.println("WHILE");
        };
    case TEST:
    {
        lf4s();
        getAtJunction();
        if (atJunction == true){
            ML-> setSpeed(0);
            MR -> setSpeed(0);
            openMechanism();
            ML ->run(BACKWARD);
            MR ->run(BACKWARD);
            ML-> setSpeed(power);
            MR -> setSpeed(power);
            delay(5000);
            ML-> setSpeed(0);
            MR -> setSpeed(0);
        }
    }

    default:
        // By default continue following the line
        lf4s();
        //Serial.print(colour1read());
        //Serial.println(" ");
        //Serial.println("Line following");
    }

    // Check the interrupt
    pauseButton();
}