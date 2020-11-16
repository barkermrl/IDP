void lf1s();
void lf4s();
void followCurve();

#ifndef LS_VAR
#define LS_VAR

// 4 sensor line following
extern double kw;
extern int dir;
extern const int kw_min;
extern int power;

// Single sensor line following
extern bool change;

#endif 
