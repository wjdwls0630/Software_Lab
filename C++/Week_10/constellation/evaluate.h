#ifndef __EVALUATE

#define __EVALUATE

#include <cmath>
#include "variables.h"

class Cevaluate {
public:
    Cevaluate() {};
    char *DecodedData;  // from the receiver
    char *Data;         // from the sender
    void evaluate();

    float BER;
};

#endif
