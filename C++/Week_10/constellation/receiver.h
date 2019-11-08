#ifndef __RECEIVER
#define __RECEIVER

#include <cmath>
#include "variables.h"

class Creceiver {
public:
    Creceiver();

    float *r; // corrupted signal = received signal
    float constellation[Nbits];
    char DecodedData[Nbits];

    void demodulate();

    int detectSymbol(float *, float *);

    float *c0t, *c1t;
};

#endif
