#include "channel.h"

void Cchannel::AWGN() {
    std::default_random_engine generator;
    std::normal_distribution<double> distribution(0.0, No);

    int NN = Nbits / Nbitspersymbol * Nsamplespersymbol;
    for (int i = 0; i < NN; i++) {
        r[i] = s[i] + distribution(generator);
    }
}