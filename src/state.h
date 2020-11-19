#ifndef STATE_VAR
#define STATE_VAR

extern int numB;            //number of blue targets delivered
extern int numR ;           //number of red targets delivered
extern int tunnelSide;      //which side of the tunnel are we currently
extern int untilJunction;   //number of "junction detections" until we actually hit a junction
extern bool atJunction;     //currently not at a junction
extern int currentBlock;    //2 for blue 1 for red 0 for empty
extern int direction;       //-1 for AC 1 for C.
extern int start;           //a variable that calls for the start/end sequence
extern int phase;           //the phase we are currently in
extern int directionSPIN; 

#endif 

void getAtJunction();
