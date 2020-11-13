#include <Arduino.h>
#include "variables.h"
#include "electronics.h"

void juncTest(){
    if (ROnLine()){
        delay(50);
        if(ROnLine()){
            junc = true;
        }
        
    }
    if (LOnLine()){
        delay(50);
        if(LOnLine()){
            junc = true;
        }
    }
}