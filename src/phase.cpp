#include "state.h"

void getPhase(){

    if (start == 1 && numB == 0 && numR == 0){
        phase = 1; //start phase (getting to the oval)
    }
    else if (start == 0 && numB < 2 && numR == 0){
        phase = 2; //second phase (delivering the blue blocks to the square)
    }
    else if (start == 0 && numB == 2 && numR <2){
        phase = 3; //third phase (delivering the red blocks to their targets)
    }
    else if (start ==1 && numB ==2 && numR == 2){
        phase = 4; //4th phase (return to start area)
    }
    else
    {
        phase = 5;
    }
    
}