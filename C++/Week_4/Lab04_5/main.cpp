//
// Created by ParkJungJin on 2019-09-22.
//

#include <iostream>
#include <iomanip>
#include <fstream>
#include <cmath>
#include <chrono>

using ns = std::chrono::nanoseconds;
using get_time = std::chrono::steady_clock;

float signal(const float &t);

float diff_original(const float &t);

float diff_approx1(const float &t, const float &dt);

float diff_approx2(const float &t, const float &dt);

float diff_approx3(const float &t, const float &dt);

void time_checker(float &t, float &dt, float(*diff_approx)(const float &, const float &));

int main() {

    std::ofstream out("data.txt", std::ios::out);

    if (!out) {
        std::cerr << "Cannot open data.txt file" << '\n';
        return -1;
    }

    float dt = 0.0001;
    float t = 1.5;
    time_checker(t, dt, (diff_approx1));
    time_checker(t, dt, (diff_approx2));
    time_checker(t, dt, (diff_approx3));

    out.close();
    return 1;
}

float signal(const float &t) {
    return 2 * sin(2 * M_PI * 100. * t);
}

float diff_original(const float &t) {
    return 440.0 * M_PI * cos(2 * M_PI * 220.0 * t);
}

float diff_approx1(const float &t, const float &dt) {
    return (signal(t + dt) - signal(t)) / dt;
}

float diff_approx2(const float &t, const float &dt) {
    return (signal(t + dt) - signal(t - dt)) / 2 * dt;
}

float diff_approx3(const float &t, const float &dt) {
    return (signal(t + dt / 2) - signal(t - dt / 2)) / dt;
}

void time_checker(float &t, float &dt, float(diff_approx)(const float &, const float &)) {
    auto start = get_time::now();
    diff_approx(t, dt);
    auto end = get_time::now();
    auto time_diff = end - start;
    std::cout << "Elapsed time : " << std::chrono::duration_cast<ns>(time_diff).count() << "ns" << '\n';
}