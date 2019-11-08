//
// Created by ParkJungJin on 2019-09-22.
//

#include <iostream>
#include <fstream>
#include <cmath>

float signal(float &t, float &f);

int main() {
    //file open
    std::ofstream out("data.txt", std::ios::out);
    std::ofstream out_alias("data_alias.txt", std::ios::out);

    if (!out) {
        std::cerr << "Cannot open data.txt file" << '\n';
        return -1;
    }

    if (!out_alias) {
        std::cerr << "Cannot open data_alias.txt file" << '\n';
        return -1;
    }

    //sine signal : sine 220Hz, sampling freq : 8kHz
    float f = 220, fs = 8 * pow(10, 3), dt = 1 / fs;
    float T = 10. / f; // 10 period

    float fs_alias = 150, dt_alias = 1 / fs_alias; // check alias

    for (float t = 0; t < T; t += dt) {
        out << t << " " << signal(t, f) << '\n';
    }

    for (float t = 0; t < T; t += dt_alias) {
        out_alias << t << " " << signal(t, f) << '\n';
    }
    out.close();
    out_alias.close();
    return 0;
}

float signal(float &t, float &f) {
    return sin(2. * M_PI * f * t);
}