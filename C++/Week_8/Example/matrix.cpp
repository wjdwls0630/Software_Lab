// matrix.cpp: 콘솔 응용 프로그램의 진입점을 정의합니다.
//

#include "stdfax.h"
#include <iostream>
#include <fstream>

using namespace std;

void matrixadd(int, int, float *, float *, float *);

void matrixmult(int, int, int, float *, float *, float *);

//void showmatrix(int, int, float*);
int main() {
    float A[] = {1, 2, 3, 4, 5, 6};
    float *B, C[6];
    B = new float[4];
    B[0] = 0;
    B[1] = 1;
    B[2] = 3;
    B[3] = 2;

    matrixmult(3, 2, 2, A, B, C);
    //showmatrix(3, 2, C);
    ofstream myout;
    myout.open("mt.dat", ios::binary | ios::out);
    myout.write((char *) A, 6 * sizeof(float));
    myout.write((char *) B, 4 * sizeof(float));
    myout.write((char *) C, 6 * sizeof(float));
    myout.close();
    getchar();
    return 0;
}

// (N by K) C X (K by M) D = (N by M) E
void matrixmult(int N, int K, int M, float *C, float *D, float *E) {
    int n, k, m;
    for (n = 0; n < N; n++) {
        for (m = 0; m < M; m++) {
            float sum = 0;
            for (k = 0; k < K; k++) sum += C[n * K + k] * D[k * M + m];
            E[n * M + m] = sum;
        }
    }
}

void matrixadd(int N, int M, float *C, float *D, float *E) {
    int NN = N * M;
    for (int i = 0; i < NN; i++) E[i] = C[i] + D[i];
}
/*void showmatrix(int N, int M, float*F) {
	int n, m;
	for (n = 0; n < N; n++) {
		for (m = 0; m < M; m++) cout << F[n*M + m] << "\t";
		cout << "\n";
	}
}*/
