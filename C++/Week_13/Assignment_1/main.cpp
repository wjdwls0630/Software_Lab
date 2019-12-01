//
// Created by ParkJungJin on 2019-11-24.
//

#include <ctime>
#include "./matrix_jin/matrix_jin.hpp"
#include "./dft_jin/dft_jin.hpp"
#include "./fft_jin/fft_jin.hpp"

using ns = std::chrono::nanoseconds;
using get_time = std::chrono::steady_clock;

void create_signal(int signal_num, std::complex<double> *signal, int signal_N);

/***************************************************************************
*	Main program
**************************************************************************/
int main() {
    //Test code
    /*
    //setting number of data
    int N = 128;

    std::complex<double> *signal = nullptr;
    signal = new std::complex<double>[N];
    create_signal(1, signal, N);
    matrix_jin<std::complex<double>> *x_n = nullptr;
    x_n = new matrix_jin<std::complex<double>>(N, 1, "x[n]", signal);
    */
    //Test1 DFT
    /*
    dft_jin<double> *dft = nullptr;
    dft = new dft_jin<double>(FT_Data::N, x_n);
    dft->writeFile_x_n_MagPh("../data/Test1/x_n_1_MagPh.txt");
    dft->writeFile_x_n_ReIm("../data/Test1/x_n_1_ReIm.txt");
    dft->writeFile_X_k_MagPh("../data/Test1/X_k_1_MagPh.txt");
    dft->writeFile_X_k_ReIm("../data/Test1/X_k_1_ReIm.txt");
    delete dft;

    dft_jin<double>* dft_idft_test = nullptr;
    dft_idft_test = new dft_jin<double>();
    dft_idft_test->readFile_X_k_MagPh("../data/Test1/X_k_1_MagPh.txt");
    dft_idft_test->writeFile_x_n_ReIm("../data/Test1/x_n_1_ReIm_test.txt");
    delete dft_idft_test;
     */
    //Test1 end

    //Test2 DFT
    /*
    dft_jin<double> *dft_1 = nullptr;
    dft_1 = new dft_jin<double>();
    dft_1 -> readFile_X_k_MagPh("../data/Test2/DFTofSquare.txt", 2);
    dft_1 -> writeFile_x_n_MagPh("../data/Test2/DFTofSquare_IDFT.txt");
    delete dft_1;

    dft_jin<double> *dft_2 = nullptr;
    dft_2 = new dft_jin<double>();
    dft_2 -> readFile_x_n_ReIm("../data/Test2/IDFTofLPF.txt", 2);
    dft_2 -> writeFile_X_k_MagPh("../data/Test2/IDFTofLPF_DFT.txt");
    delete dft_2;
     */
    //Test2 end

    //Test3 FFT
    /*
    fft_jin<double> *fft = nullptr;
    fft = new fft_jin<double>(FT_DATA::N, x_n);
    fft->writeFile_x_n_MagPh("../data/Test3/x_n_1_MagPh.txt");
    fft->writeFile_x_n_ReIm("../data/Test3/x_n_1_ReIm.txt");
    fft->writeFile_X_k_MagPh("../data/Test3/X_k_1_MagPh.txt");
    fft->writeFile_X_k_ReIm("../data/Test3/X_k_1_ReIm.txt");
    delete fft;

    fft_jin<double>* fft_idft_test = nullptr;
    fft_idft_test = new fft_jin<double>();
    fft_idft_test->readFile_X_k_MagPh("../data/Test3/X_k_1_MagPh.txt");
    fft_idft_test->writeFile_x_n_ReIm("../data/Test3/x_n_1_ReIm_test.txt");
    delete fft_idft_test;
     */
    //Test3 end


    //create signal
    // N =128
    // 1. signal x[n] =1 (n<10, n>118)
    // 2. signal x[n] =cos(8*pi*n/N)
    // 3. signal x[n] =sin(16*pi*n/N)

    //setting number of data
    int N = 128;

    std::complex<double> *signal = nullptr;
    signal = new std::complex<double>[N];
    create_signal(1, signal, N);
    matrix_jin<std::complex<double>> *x_n = nullptr;
    x_n = new matrix_jin<std::complex<double>>(N, 1, "x[n]", signal);

    //compare computation time DFT vs FFT

    //1. signal x[n] =1 (n<10, n>118)
    dft_jin<double> *dft = nullptr;
    auto start = get_time::now();
    dft = new dft_jin<double>(FT_DATA::N, x_n);
    auto end = get_time::now();
    auto time_diff = end - start;
    std::cout << "signal x[n] =1 (n<10, n>118) DFT Computation Time : " <<
              std::chrono::duration_cast<ns>(time_diff).count() * pow(10, -3) << "us" << '\n';
    dft->writeFile_x_n_ReIm("../data/main/x_n_1_ReIm.txt");
    dft->writeFile_X_k_MagPh("../data/main/X_k_1_MagPh_DFT.txt");
    delete dft;

    fft_jin<double> *fft = nullptr;
    start = get_time::now();
    fft = new fft_jin<double>(FT_DATA::N, x_n);
    end = get_time::now();
    time_diff = end - start;
    std::cout << "signal x[n] =1 (n<10, n>118) FFT Computation Time : " <<
              std::chrono::duration_cast<ns>(time_diff).count() * pow(10, -3) << "us" << '\n';
    fft->writeFile_X_k_MagPh("../data/main/X_k_1_MagPh_FFT.txt");
    delete fft;

    delete signal;
    delete x_n;

    //2. signal x[n] =cos(8*pi*n/N)

    signal = new std::complex<double>[N];
    create_signal(2, signal, N);
    x_n = new matrix_jin<std::complex<double>>(N, 1, "x[n]", signal);

    start = get_time::now();
    dft = new dft_jin<double>(FT_DATA::N, x_n);
    end = get_time::now();
    time_diff = end - start;
    std::cout << "signal x[n] =cos(8*pi*n/N) DFT Computation Time : " <<
              std::chrono::duration_cast<ns>(time_diff).count() * pow(10, -3) << "us" << '\n';
    dft->writeFile_x_n_ReIm("../data/main/x_n_2_ReIm.txt");
    dft->writeFile_X_k_MagPh("../data/main/X_k_2_MagPh_DFT.txt");

    start = get_time::now();
    fft = new fft_jin<double>(FT_DATA::N, x_n);
    end = get_time::now();
    time_diff = end - start;
    std::cout << "signal x[n] =cos(8*pi*n/N) FFT Computation Time : " <<
              std::chrono::duration_cast<ns>(time_diff).count() * pow(10, -3) << "us" << '\n';
    fft->writeFile_X_k_MagPh("../data/main/X_k_2_MagPh_FFT.txt");

    //3. signal x[n] =sin(16*pi*n/N)

    signal = new std::complex<double>[N];
    create_signal(2, signal, N);
    x_n = new matrix_jin<std::complex<double>>(N, 1, "x[n]", signal);

    start = get_time::now();
    dft = new dft_jin<double>(FT_DATA::N, x_n);
    end = get_time::now();
    time_diff = end - start;
    std::cout << "signal x[n] =sin(16*pi*n/N) DFT Computation Time : " <<
              std::chrono::duration_cast<ns>(time_diff).count() * pow(10, -3) << "us" << '\n';
    dft->writeFile_x_n_ReIm("../data/main/x_n_3_ReIm.txt");
    dft->writeFile_X_k_MagPh("../data/main/X_k_3_MagPh_DFT.txt");

    start = get_time::now();
    fft = new fft_jin<double>(FT_DATA::N, x_n);
    end = get_time::now();
    time_diff = end - start;
    std::cout << "signal x[n] =sin(16*pi*n/N) FFT Computation Time : " <<
              std::chrono::duration_cast<ns>(time_diff).count() * pow(10, -3) << "us" << '\n';
    fft->writeFile_X_k_MagPh("../data/main/X_k_3_MagPh_FFT.txt");
    
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
    } else if (signal_num == 2) {
        for (int i = 0; i < signal_N; i++) {
            *(signal + i) = std::complex<double>(cos(8.0 * M_PI * i / signal_N), 0);
        }
    } else if (signal_num == 3) {
        for (int i = 0; i < signal_N; i++) {
            *(signal + i) = std::complex<double>(sin(16.0 * M_PI * i / signal_N), 0);
        }
    }
}

