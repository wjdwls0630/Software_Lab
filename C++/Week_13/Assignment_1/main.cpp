//
// Created by ParkJungJin on 2019-11-24.
//

#include "./matrix_jin/matrix_jin.hpp"
#include "./dft_jin/dft_jin.hpp"


void create_signal(int signal_num, std::complex<double> *signal, int signal_N);

/***************************************************************************
*	Main program
**************************************************************************/
int main() {

    //create signal
    // N =128
    //signal x[n] =1 (n<10, n>118)

    //setting number of data
    int N = 128;

    std::complex<double> *signal = nullptr;
    signal = new std::complex<double>[N];
    create_signal(1, signal, N);
    matrix_jin<std::complex<double>> *x_n = nullptr;
    x_n = new matrix_jin<std::complex<double>>(N, 1, "x[n]", signal);

    dft_jin<double> *dft = nullptr;
    dft = new dft_jin<double>(FT_Data::N, x_n);
    dft->writeFile_x_n_MagPh("../data/x_n_1_MagPh.txt");
    dft->writeFile_x_n_ReIm("../data/x_n_1_ReIm.txt");
    dft->writeFile_X_k_MagPh("../data/X_k_1_MagPh.txt");
    dft->writeFile_X_k_ReIm("../data/X_k_1_ReIm.txt");


    return 1;
}

void create_signal(int signal_num, std::complex<double> *signal, int signal_N) {
    if (signal_num == 1) {
        for (int i = 0; i < signal_N; i++) {
            if (i < 10 || i > 118) {
                *(signal + i) = std::complex<double>(1, 0);
            } else {
                *(signal + i) = std::complex<double>(0, 0);
            }
        }
    }
}

