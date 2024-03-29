// matrix_LSM.cpp: 콘솔 응용 프로그램의 진입점을 정의합니다.
///
#include <iostream> // for getchar( )
#include <fstream> // for FILE
#include <cstdlib>  // for rand( )
#include <cmath>  // for exp( )
#include "myMatrix.h"

using namespace std;

int main() {
    // data generation
    float datax[100], datay[100];
    int N, i;
    ifstream data1("data2.txt");
    data1 >> N;
    for (i = 0; i < N; i++) {

        data1 >> datax[i] >> datay[i];
    }
    data1.close();
    // LSM
    float A[9], B[3], C[3];
    for (i = 0; i < 9; i++) A[i] = 0.0;
    for (i = 0; i < 3; i++) B[i] = C[i] = 0.0;
    for (i = 0; i < N; i++) {
        float x, x2, x3, x4, y, xy, x2y;
        x = datax[i];
        x2 = x * x;
        x3 = x2 * x;
        x4 = x3 * x;
        y = datay[i];
        xy = y * x;
        x2y = y * x2;
        A[0] += x2;
        A[1] += x;
        A[2] += 1.0;
        B[0] += y;
        A[3] += x3;
        A[4] += x2;
        A[5] += x;
        B[1] += xy;
        A[6] += x4;
        A[7] += x3;
        A[8] += x2;
        B[2] += x2y;
    }

    GaussElimination(3, A, B);

    cout << "y = " << B[0] << " x**2 + " << B[1] << " x + " << B[2] << "\n";

    getchar();

    return 0;
}

