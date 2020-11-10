#include <Arduino.h>
#define ls1 6
#define ls2 7 //Middle sensor
#define ls3 8
#define kp 50

void shft(double *svg, int len, double IN);
void update(double *svg1, double *svg2, double *svg3, int len);