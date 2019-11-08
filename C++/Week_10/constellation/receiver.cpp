#include "receiver.h"
#include "myMatrix.h"

Creceiver::Creceiver() {

    float t = 0.0, T = 0.01;
    float dt = T / Nsamplespersymbol;
    c0t = new float[Nsamplespersymbol];
    c1t = new float[Nsamplespersymbol];
    for (int i = 0; i < Nsamplespersymbol; i++, t += dt) {
        c0t[i] = cos(2. * 3.141592 * t / T);
        c1t[i] = sin(2. * 3.141592 * t / T);
    }
}

void Creceiver::demodulate() {
    int nn = Nsamplespersymbol / Nbitspersymbol;
    for (int i = 0; i < Nbits; i += 2) {
        int symbol = detectSymbol(constellation + i, r + i * nn);
        if (symbol == 0) {
            DecodedData[i] = 0;
            DecodedData[i + 1] = 0;
        } else if (symbol == 1) {
            DecodedData[i] = 1;
            DecodedData[i + 1] = 0;
        } else if (symbol == 2) {
            DecodedData[i] = 1;
            DecodedData[i + 1] = 1;
        } else {
            DecodedData[i] = 0;
            DecodedData[i + 1] = 1;
        }
    }
}

int Creceiver::detectSymbol(float *co, float *rr) {
    float dummy[Nbitspersymbol];
    co[0] = dot(Nsamplespersymbol, rr, c0t);
    co[1] = dot(Nsamplespersymbol, rr, c1t);
    if (co[0] >= 0 && co[1] >= 0) return 0;
    else if (co[0] < 0 && co[1] >= 0) return 1;
    else if (co[0] < 0 && co[1] < 0) return 2;
    return 3;
}