#include <Arduino.h>
#include "variables.h"
#include "electronics.h"

void lf4(){// Line is 2cm wide, Targets are 7.5cm wide

if (dir == -1 && LMOnLine()){
    dir = dir*-1;
    kw = kw_min;
    updateSpeed();
}
if (dir == 1 && RMOnLine()){
    kw = kw_min;
    dir = dir*-1;
    updateSpeed();
}
else{
   kw = kw + 0.7;
   updateSpeed();
   Serial.println(kw);
}
}
