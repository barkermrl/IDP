#ifndef LS_H
#define LS_H

void lf4s();
void toggleDir();
void skipJunc();
void lf4s_dummy();

// PID controller functions
// void pid();
void pidUpdateSpeed();
void resetID();

// Add reverse functions in
void ReverseLf4s();
void ReversePidUpdateSpeed();

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
