#include <iostream>
#include "myMatrix.h"

using namespace std;

void scalarmult(int n, int m, float a, float *b, float *c) {
    int N = n * m;
    for (int i = 0; i < N; i++) c[i] = a * b[i];
}

void matrixadd(int n, int m, float *a, float *b, float *c) {
    int N = n * m;
    for (int i = 0; i < N; i++) c[i] = a[i] + b[i];
}

// (N by K) C X (K by M) D = (N by M) E 
void matrixmult(int N, int K, int M, float *C, float *D, float *E) {
    int n, k, m;
    for (n = 0; n < N; n++)
        for (m = 0; m < M; m++) {
            float sum = 0;
            for (k = 0; k < K; k++) sum += C[n * K + k] * D[k * M + m];
            E[n * M + m] = sum;
        }
}

void showMatrix(int n, int m, float *F) {
    int i, j;
    for (i = 0; i < n; i++) {
        for (j = 0; j < m; j++) cout << F[i * m + j] << "\t";
        cout << "\n";

    }
}

void showMatrix(char *name, int n, int m, float *F) {
    cout << name << endl;
    showMatrix(n, m, F);
}