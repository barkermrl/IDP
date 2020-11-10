#include <Arduino.h>
#define ls1 6
#define ls2 7 //Middle sensor
#define ls3 8
#define kp 50 //proportional coeff for control using running averages
#define kw 10 //oscilatory coeff for control using single sensor. Higher kw causes higher oscilations

void shft(double *svg, int len, double IN);
void update(double *svg1, double *svg2, double *svg3, int len);