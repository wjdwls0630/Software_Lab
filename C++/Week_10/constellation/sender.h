#ifndef __SENDER
#define __SENDER

#include <cmath>
#include "variables.h"
#include <cstdlib>
#include <ctime>

using namespace std;

class Csender {
public:
    Csender();

    char data[Nbits];
    float s[Nbits / Nbitspersymbol * Nsamplespersymbol]; // trasmitted signal
    void transmitData();

    void generateSymbol(float, float, float *);

    float *c0t, *c1t;
};

#endif
