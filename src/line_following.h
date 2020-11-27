#ifndef LS_H
#define LS_H

void lf4s();
void toggleDir();
void skipJunc();

// PID controller functions
void pid();
void pidUpdateSpeed();
// PID power_difference (used when detecting junctions)
extern int power_difference;

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

#endif
