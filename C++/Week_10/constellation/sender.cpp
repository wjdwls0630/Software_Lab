#include "sender.h"
#include "myMatrix.h"

Csender::Csender() {
    float t = 0.0, T = 0.01;
    float dt = T / Nsamplespersymbol;
    c0t = new float[Nsamplespersymbol];
    c1t = new float[Nsamplespersymbol];
    for (int i = 0; i < Nsamplespersymbol; i++, t += dt) {
        c0t[i] = cos(2. * 3.141592 * t / T);
        c1t[i] = sin(2. * 3.141592 * t / T);
    }
}

void Csender::transmitData() {
    std::default_random_engine generator;
    std::normal_distribution<double> distribution(0.0, No);
    float A = sqrt(Eb);
    for (int i = 0; i < Nbits; i++) data[i] = rand() % 2;
    for (int i = 0; i < Nbits; i += 2) {
        if (data[i] == 0 && data[i + 1] == 0) generateSymbol(A, A, s + i * Nsamplespersymbol / Nbitspersymbol);
        if (data[i] == 1 && data[i + 1] == 0) generateSymbol(-A, A, s + i * Nsamplespersymbol / Nbitspersymbol);
        if (data[i] == 1 && data[i + 1] == 1) generateSymbol(-A, -A, s + i * Nsamplespersymbol / Nbitspersymbol);
        if (data[i] == 0 && data[i + 1] == 1) generateSymbol(A, -A, s + i * Nsamplespersymbol / Nbitspersymbol);
    }
}

void Csender::generateSymbol(float a, float b, float *ss) {
    float dummy[Nsamplespersymbol];
    scalarmult(1, Nsamplespersymbol, a, c0t, ss);
    scalarmult(1, Nsamplespersymbol, b, c1t, dummy);
    matrixadd(1, Nsamplespersymbol, dummy, ss, ss);
}