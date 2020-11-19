#ifndef STATE_VAR
#define STATE_VAR

extern int numB;            //number of blue targets delivered
extern int numR ;           //number of red targets delivered
extern int untilJunction;   //number of "junction detections" until we actually hit a junction
extern bool atJunction;     //currently not at a junction
extern int currentBlock;    //2 for blue 1 for red 0 for empty
extern int direction;       //-1 for AC 1 for C.
extern int start;           //a variable that calls for the start/end sequence
extern int phase;           //the phase we are currently in

// Where we are
enum location_status
{
    HOME, // Starting square
    TUNNEL, // In the tunnel stretch
    BLUE_DELIVERY, // In the blue delivery zone 
    LOOP, // In the loop with the red blocks
};
extern location_status location;
#endif 

void getAtJunction();
