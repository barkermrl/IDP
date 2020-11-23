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
#endif

output_status makeDecision();
output_status spinToggleJunction();
void getPhase();
void toggleDirection();

