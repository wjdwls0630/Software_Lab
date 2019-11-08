//
// Created by ParkJungJin on 2019-09-22.
//

#include <iostream>
#include <iomanip>
#include <fstream>
#include <cmath>


float signal(float &t);

float diff_original(float &t);

float diff_approx(float &t, float &dt);

int main() {
    std::ofstream out("data.txt", std::ios::out);

    if (!out) {
        std::cerr << "Cannot open data.txt file" << '\n';
        return -1;
    }

    float dt = 1.;
    for (float dt = 1.0; dt > pow(10, -7); dt *= 0.1) {
        float t = 0.;
        out << dt << " " << 1 / dt << '\n';
        for (int i = 0; i < 50; i++) {
            out << t << " " << diff_original(t) << " " << diff_approx(t, dt) << '\n';
            t += dt;
        }
    }
    out.close();
    return 1;
}

float signal(float &t) {
    return sin(2 * M_PI * 220.0 * t);
}

float diff_original(float &t) {
    return 440.0 * M_PI * cos(2 * M_PI * 220.0 * t);
}

float diff_approx(float &t, float &dt) {
    float k = t + dt;
    return (signal(k) - signal(t)) / dt;
}