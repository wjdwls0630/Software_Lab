//
// Created by ParkJungJin on 2019-09-30.
//

#include <iostream>
#include <cstdlib>


int main() {
    int *hits;
    hits = new int[6]{};
    int Ntry = 100000;

    //init
    for (int i = 0; i < 6; ++i) {
        hits[i] = 0;
    }

    for (int j = 0; j < Ntry; ++j) {
        hits[std::rand() % 6]++;
    }

    std::cout << "N = " << Ntry << "\n\n";

    for (int k = 0; k < 6; ++k) {
        std::cout << "P[" << k + 1 << "] = " << (double) hits[k] / Ntry << "\n";
    }


    return 1;
}

