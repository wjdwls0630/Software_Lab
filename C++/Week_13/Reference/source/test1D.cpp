/***********************************
 test complex operation
 author : Doug Young Suh
 date   : 99.9.17

  Revision 1: 2000.8.25 Doug Young Suh 
   include fft test.
  Revision 2: 2013. 1. 8 
   Read an image and fft line by line
  Revision 3: 2014. 4. 30  ==> delete
   add two more test
   (square) <--> (sinc)
   (sinc)   <--> (square)
  Revision 4: 2014. 5. 11
   only 1 dimensional FFT  (Fft1D.hpp Fft1D.cpp)
  Revision 5: 2019. 5. 11
   use the complex class in C++
   stdio.h --> fstream
***************************************/
//#include <stdio.h>
//#include <stdlib.h>
//#include <conio.h>
#include <iostream>
#include <fstream>
#include <complex>
#include "fft1D.hpp"

void main() {
    ofstream fff("DFTofSquare.txt"), ggg("IDFTofLPF.txt");
    long n, k;
    /////////////////////////////////////////
    FFT *sequence;
    sequence = new FFT(512);
    int N = 512;

    // test 1: DFT of square x[n]
    for (n = 0; n < N; n++) sequence->x[n] = complex<Real>(0.0, 0.0);
    for (n = 0; n < 16; n++) sequence->x[n] = complex<Real>(1.0, 0.0);
    for (n = N - 15; n < N; n++) sequence->x[n] = complex<Real>(1.0, 0.0);
    sequence->ForwardFFT();
    if (!fff) {
        cout << "cant open DFTofSquare.txt.\n";
        exit(333);
    }

    for (k = N / 2; k < N - 1; k++) fff << real(sequence->X[k]) << endl;
    for (k = 0; k < N / 2 + 1; k++) fff << real(sequence->X[k]) << endl;
    fff.close();

    // test 2: DFT of ideal low pass filter X[k]
    for (k = 0; k < N; k++) sequence->X[k] = complex<Real>(0.0, 0.0);
    for (k = 0; k < 16; k++) sequence->X[k] = complex<Real>(1.0, 0.0);
    for (k = N - 15; k < N; k++) sequence->X[k] = complex<Real>(1.0, 0.0);
    sequence->InverseFFT();
    if (!ggg) {
        cout << "cant open IDFTofLPF.txt.\n";
        exit(334);
    }
    for (n = N / 2; n < N - 1; n++) ggg << real(sequence->x[n]) << endl;
    for (n = 0; n < N / 2 + 1; n++) ggg << real(sequence->x[n]) << endl;
    ggg.close();

    exit(400);
}

