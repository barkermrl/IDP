void lf1s(int power, int kw_min, bool change);
void lf4s(int power, int kw_min);
void followCurve();

#ifndef LF_VARIABLES
#define LF_VARIABLES

// 4 sensor line following
extern double kw;
extern int dir;

// Single sensor line following
extern bool change;

#endif