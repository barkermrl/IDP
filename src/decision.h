int makeDecision();

enum output_status
{
    SPIN_180 = 0,
    SPIN_90_L = 1,
    SPIN_90_R = 2,
    FOLLOW_LINE = 3,
    FOLLOW_CURVE = 4,
    STOP = 4,
};