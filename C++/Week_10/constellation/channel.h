#ifndef __CHANNEL

#define __CHANNEL

#include <cmath>
#include <random>
#include "variables.h"

class Cchannel {
public:
    Cchannel() {};
    float *s; // trasmitted signal
    float r[Nbits / Nbitspersymbol * Nsamplespersymbol]; // corrupted signal
    void AWGN();
};

#endif