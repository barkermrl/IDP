#ifndef DECISION_H
#define DECISION_H
enum output_status
{
    SPIN_L,
    SPIN_R,
    FOLLOW_LINE,
    FOLLOW_CURVE ,
    GRAB_BLOCK,
    RELEASE_BLOCK,
    STOP,
    PANIC,
    FINISH,
    TEST,
};

output_status makeDecision();
output_status returnSpinToggleJunction();
void spinToggleJunction();
void grabBlock(bool moving);
void moveUntilBlock();
void moveUntilJunction();
void releaseBlock();
void followLineForwards(int iterations);
void getPhase();
void toggleDirection();
#endif



