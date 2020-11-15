int makeDecision(int numB, int numR, int tunnelSide, int untilJunction,
                 bool atJunction, int currentBlock, int direction);

enum output_status
{
    SPIN_180 = 0,
    SPIN_90_L = 1,
    SPIN_90_R = 2,
    FOLLOW_LINE = 3,
    FOLLOW_CURVE = 4,
};