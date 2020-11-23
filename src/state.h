#ifndef STATE_VAR
#define STATE_VAR

extern int numB;          //number of blue targets delivered
extern int numR;          //number of red targets delivered
extern int untilJunction; //number of "junction detections" until we actually hit a junction
extern bool atJunction;   //currently not at a junction
extern int start;         //a variable that calls for the start/end sequence
extern int phase;         //the phase we are currently in
extern int turning;       //1 if we are turning, 0 if we are not turning
extern int counter;       //test variable
extern bool blockAhead;   //if there is a block ahead

// Current block in grabber
enum currentBlock_status
{
    BLUE,
    RED,
    EMPTY,
};
extern currentBlock_status currentBlock;

// Direction around the loop
enum direction_status
{
    ANTICLOCKWISE, // AC
    CLOCKWISE,     // C
    NONE,          // Not in loop
};
extern direction_status direction; //-1 for AC 1 for C.

// Where we are
enum location_status
{
    HOME,          // Starting square
    TUNNEL,        // In the tunnel stretch
    BLUE_DELIVERY, // In the blue delivery zone
    LOOP,          // In the loop with the red blocks
};
extern location_status location;

void getBlockAhead();
void getAtJunction();
void getUntilJunc();
#endif


