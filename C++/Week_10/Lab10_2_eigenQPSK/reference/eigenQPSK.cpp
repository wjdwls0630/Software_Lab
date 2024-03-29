//////////////////////////////////////////////////// 
//   QPSK simulation
//   Author: Doug Young Suh
//   Date  : Oct. 25, 2019
////////////////////////////////////////////////////
#include "stdafx.h"
#include <iostream>
#include <eigen/Dense>
#include <eigen/LU>

#define N 20    // dimension of basis vector
#define M 20    // number of data bits
#define A 10.0  // signal amplitude
using namespace Eigen;
using namespace std;

#include "basis.h"

int main() {
    // make 2 basis vectors
    basis c0, c1;
    c0 = basis(N, 0); // cos
    c1 = basis(N, 1); // sin
    // check orthonormality
    cout << "c0 c1 " << c0.c.dot(c1.c) << endl;
    cout << "c0 c0 " << c0.c.dot(c0.c) << endl;
    cout << "c1 c1 " << c1.c.dot(c1.c) << endl;

    //////  sender /////
    VectorXd data = VectorXd(M);      // M bits
    VectorXd *s = new VectorXd[M / 2];  // M/2 symbols QPSK(2bits/symbol)
    for (int i = 0; i < M / 2; i++) {
        data[2 * i] = (rand() % 2) * 2 - 1;   // 1 or -1
        data[2 * i + 1] = (rand() % 2) * 2 - 1; // 1 or -1
        s[i] = A * data[2 * i] * c0.c + A * data[2 * i + 1] * c1.c;
    }
    cout << "data " << data << endl;
    // channel //
    VectorXd *r = new VectorXd[M / 2];
    for (int i = 0; i < M / 2; i++) {
        r[i] = s[i];
        r[i][j] +=
    }
    ///  receiver ///
    VectorXd decodedData = VectorXd(M);
    VectorXd b0 = VectorXd(M / 2);
    VectorXd b1 = VectorXd(M / 2);
    for (int i = 0; i < M / 2; i++) {
        b0[i] = r[i].dot(c0.c);
        b1[i] = r[i].dot(c1.c);
        // decision
        // .... b0[], b1[] --> decodeData[]
        decodedData[2 * i] = b0[i] / A;
        decodedData[2 * i + 1] = b1[i] / A;
    }
    VectorXd error = data - decodedData;
    cout << "data " << decodedData << endl;
    cout << "error " << error << endl;
    getchar();
    return 0;
}

