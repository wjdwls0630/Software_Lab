#include "evaluate.h"

void Cevaluate::evaluate() {
    float errors = 0;
    for (int i = 0; i < Nbits; i++) if (Data[i] != DecodedData[i]) errors += 1;
    BER = errors / Nbits;
}