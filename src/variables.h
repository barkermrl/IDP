#ifndef VARIABLES_H
#define VARIABLES_H

extern const int kw_min;
extern int kp;    //proportional coeff for control using running averages
extern double kw; //oscilatory coeff for control using single sensor. Higher kw causes higher oscilations
extern int power; // average speed of motors
extern bool junc; //variable to tell wether or not we are at a junction
extern int side;

// Variables for the single sensor line follower:
extern int dir;     //1 corresponds to left, -1 to right
extern bool change; //Whether or not the robot should change directions when hitting the black
#endif