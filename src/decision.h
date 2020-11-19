#ifndef DECISION_H
#define DECISION_H
enum output_status
{
    SPIN_180,
    FOLLOW_LINE,
    FOLLOW_CURVE ,
    STOP,
};
#endif

output_status makeDecision();
void getPhase();

