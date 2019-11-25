//
// Created by ParkJungJin on 2019-11-21.
//

#include "antenna_jin.hpp"

antenna_jin::antenna_jin(double f) :
        f(f), w(2 * M_PI * this->f), k(this->w / C), T(1 / this->f),
        N_t(500), end_time(1e-6), start_time(0.), dt((this->end_time - this->start_time) / N_t),
        N_r(2000), end_r(20000), start_r(0), dr((this->end_r - this->start_r) / N_r) {
    this->Rxt = new double[N_r + 1];
    this->Rxt_plus = new double[N_r];
    this->Rxt_minus = new double[N_r + 1];
}

antenna_jin::~antenna_jin() {
    delete[] this->Rxt;
    delete[] this->Rxt_plus;
    delete[] this->Rxt_minus;
}

void antenna_jin::calculate() {
    double t, r;
    for (int tn = 0; tn < N_t; tn++) {
        t = start_time + tn * dt;
        this->Rxt_minus[0] = I0 * sin(w * t);
        this->Rxt[0] = this->Rxt_minus[0] - I0 * cos(w * t) / M_PI;
        for (int rn = 0; rn < N_r; rn++) {
            r = start_r + (rn + 1) * dr;
            this->Rxt_plus[rn] = this->Rxt[rn] + (r - dr / 2) / (r + dr / 2) * (this->Rxt[rn] - this->Rxt_minus[rn]) -
                                 k * k * this->Rxt[rn] * dr * dr / (r + dr / 2);
            this->Rxt_minus[rn + 1] = this->Rxt[rn];
            this->Rxt[rn + 1] = this->Rxt_plus[rn];
        }
        this->write2File(tn);
    }
}

int antenna_jin::write2File(int tn) {
    this->outFile.open("../data/R_tn=" + std::to_string(tn) + ".txt");
    if (!this->outFile) {
        std::cerr << "cannot open file" << '\n';
    }
    double r;
    for (int rn = 0; rn < N_r + 1; rn++) {
        r = start_r + (rn + 1) * dr;
        outFile << r << ' ' << this->Rxt[rn] << '\n';
    }
    outFile.close();
    return 1;
}





