//
// Created by ParkJungJin on 2019-11-20.
//

#include <iostream>
#include <iomanip>
#include <fstream>
#include <cmath>

float Vo = 100, a = 1, b = 2;

float Vxy(float &x, float &y);

int main() {

    //initialize variables
    double fx_dt_plus = 0, fx = 0, fx_dt_minus = 0;
    double start_time = 0; //start time
    double end_time = 6 * pow(10, -3); // end time 6ms

    // angular frequency
    double w = sqrt(abs(pow((R / L), 2) - 4.0 * 1 / (L * C)));

    //frequency
    double f = w / (2 * M_PI);

    //period
    double T = 1 / f;

    //n_T :  dt = T/n_T
    int n_T = 20;

    //dt
    double dt = T / n_T;

    //number of sampling during start time to end time
    int N = (int) ((end_time - start_time) / dt);

    //file open for record
    std::ofstream out("data.txt", std::ios::out);
    if (!out) {
        std::cerr << "Cannot open data.txt file" << '\n';
        return -1;
    }

    //
    double t = 0;
    for (int i = 0; i < N; i++) {
        t += dt;
        vt_dt_plus = (2 * vt - vt_dt_minus) - (R / L) * dt * (vt - vt_dt_minus) + (1 / (L * C)) * pow(dt, 2) * (V - vt);
        vt_dt_minus = vt;
        vt = vt_dt_plus;
        out << t << ' ' << vt_dt_minus << '\n';
    }
    out << t + dt << ' ' << vt << '\n';

    out.close();

    return 0;
}