#include <Arduino.h>
#include <Wire.h>
#include "misc_func.h"

void setup() {
  setup_auto(1); //input 1 to set up for single sensor line following and 2 to set up for 3 sensor line following
}

void loop() {
  line_follower_singleswitch();
  //lineFollower_3switch();
  //turn180();
}