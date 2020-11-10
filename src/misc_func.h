#include <Arduino.h>
#include <Wire.h>

void shft(double *svg, int len, double IN);
void update(double *svg1, double *svg2, double *svg3, int len);
void line_follower_singleswitch();
void lineFollower_3switch();
void setup_auto(int i);
void turn180();
