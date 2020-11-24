#ifndef LS_H
#define LS_H

void lf1s();
void lf4s();
void followCurve();
void toggleDir();
void skipJunc();
// 4 sensor line following
extern double kw;
enum dir_status
{
    L = 1,
    R = -1,
};
// 1 corresponds to left, -1 to right
extern dir_status dir;

extern const int kw_min;
extern int power;

// Single sensor line following
extern bool change;

#endif
