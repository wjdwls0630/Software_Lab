//
// Created by ParkJungJin on 2019-09-30.
//

#include <iostream>
#include <random>

int main() {
    //for random
    std::random_device rd;
    std::mt19937_64 rng(rd());
    std::uniform_real_distribution<double> dist(-1, 1);
    double hits;
    double x, y;


    for (int n = 1; n < 100000; n *= 10) {
        //init hit
        hits = 0;
        for (int i = 0; i < n; i++) {
            x = dist(rng);
            y = dist(rng);
            if (pow(x, 2) + pow(y, 2) < 1) {
                hits++;
            }
        }

        std::cout << "n = " << n << '\n';
        std::cout << "PI = " << M_PI << '\n';
        std::cout << "hits_pi : " << (double) hits / n * 4.0 << '\n';
        std::cout << '\n';

    }
    return 1;
}

