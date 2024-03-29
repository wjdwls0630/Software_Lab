// matrix.cpp: 콘솔 응용 프로그램의 진입점을 정의합니다.
//

#include "stdafx.h"
#include <iostream>
#include <fstream>

using namespace std;

void showmatrix(int, int, float *);

void showmatrix(char *, int, int, float *);

int main() {
    float A[6], B[4], C[6];

    ifstream myout;
    myout.open("mt.dat", ios::binary | ios::in);
    myout.read((char *) A, 6 * sizeof(float));
    myout.read((char *) B, 4 * sizeof(float));
    myout.read((char *) C, 6 * sizeof(float));
    myout.close();

    showmatrix("A", 3, 2, A);
    showmatrix("B", 2, 2, B);
    showmatrix("C=A*B", 3, 2, C);
    getchar();
    return 0;
}

void showmatrix(char *name, int N, int M, float *F) {
    cout << name << "\n";
    showmatrix(N, M, F);
}

void showmatrix(int N, int M, float *F) {
    int n, m;
    for (n = 0; n < N; n++) {
        for (m = 0; m < M; m++) cout << F[n * M + m] << "\t";
        cout << "\n";
    }
}
