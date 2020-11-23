#ifndef DECISION_H
#define DECISION_H
enum output_status
{
    SPIN_L,
    SPIN_R,
    FOLLOW_LINE,
    FOLLOW_CURVE ,
    STOP,
    PANIC,
    FINISH,
    TEST,
};
#endif

output_status makeDecision();
void getPhase();
void toggleDirection();

