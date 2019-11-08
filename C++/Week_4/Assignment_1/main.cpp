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

#define TIMESTART 0.0
#define TIMEEND 0.1

double signal(const double &t);

double diff_original(const double &t);

double diff_approx(const double &t, const double &dt);

double integrate_original(const double &t);

double integrate_approx(const double &t, const double &dt);

int main() {
    std::ofstream out("data_diff.txt", std::ios::out);

    if (!out) {
        std::cerr << "Cannot open data_diff.txt file" << '\n';
        return -1;
    }


    for (double dt = 0.1; dt > pow(10, -6); dt *= 0.1) {
        out << dt << '\n';

        //record diff
        auto start = get_time::now();
        for (double t = TIMESTART; t <= TIMEEND; t += dt) {
            out << t << " " << diff_original(t) << " " << diff_approx(t, dt) << '\n';
        }
        auto end = get_time::now();
        auto time_diff = end - start;
        out << std::chrono::duration_cast<ns>(time_diff).count() << ' ';

        //calculate snr_diff

        double sp_diff = 0.;
        double np_diff = 0.;

        for (double t = TIMESTART; t <= TIMEEND; t += dt) {
            sp_diff += (pow(fabs(diff_original(t)), 2) * dt);
            np_diff += (pow(fabs(diff_original(t) - diff_approx(t, dt)), 2) * dt);
        }
        sp_diff *= (1 / (TIMEEND - TIMESTART));
        np_diff *= (1 / (TIMEEND - TIMESTART));
        out << 10 * log10l(sp_diff / np_diff) << '\n';
    }
    out.close();

    out.open("data_integrate.txt", std::ios::out);
    if (!out) {
        std::cerr << "Cannot open data_integrate.txt file" << '\n';
        return -1;
    }

    for (double dt = 0.1; dt > pow(10, -6); dt *= 0.1) {
        out << dt << '\n';

        //record integrate
        auto start = get_time::now();
        for (double t = TIMESTART; t <= TIMEEND; t += dt) {
            out << t << " " << integrate_original(t) << " " << integrate_approx(t, dt) << '\n';

        }
        auto end = get_time::now();
        auto time_diff = end - start;
        out << std::chrono::duration_cast<ns>(time_diff).count() << ' ';

        //calculate snr_integrate

        double sp_integrate = 0.;
        double np_integrate = 0.;

        for (double t = TIMESTART; t <= TIMEEND; t += dt) {
            sp_integrate += (pow(fabs(integrate_original(t)), 2) * dt);
            np_integrate += (pow(fabs(integrate_original(t) - integrate_approx(t, dt)), 2) * dt);
        }
        sp_integrate *= (1 / (TIMEEND - TIMESTART));
        np_integrate *= (1 / (TIMEEND - TIMESTART));
        out << 10 * log10l(sp_integrate / np_integrate) << '\n';
    }


    return 1;
}

double signal(const double &t) {
    return 2 * sin(2 * M_PI * 100 * t);
}

double diff_original(const double &t) {
    return 4 * M_PI * 100 * cos(2 * M_PI * 100 * t);
}

double diff_approx(const double &t, const double &dt) {
    return (signal(t + (dt / 2)) - signal(t - (dt / 2))) / dt;
}

double integrate_original(const double &t) {
    return (2. / (2 * M_PI * 100)) * cos(2 * M_PI * 100 * TIMESTART) -
           (2. / (2 * M_PI * 100)) * cos(2 * M_PI * 100 * t);
}

double integrate_approx(const double &t, const double &dt) {
    double sum = 0.;
    for (double i = TIMESTART; i < t; i += dt) {
        sum += signal(i) * dt;
    }
    return sum;
}

