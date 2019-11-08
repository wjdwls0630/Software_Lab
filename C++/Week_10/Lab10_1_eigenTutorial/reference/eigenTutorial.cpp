// eigenTutorial.cpp: 콘솔 응용 프로그램의 진입점을 정의합니다.
//
#include "../../stdafx/stdafx1.h"

#include <iostream>
#include <eigen/Dense>
#include <eigen/LU>

using namespace Eigen;
using namespace std;


int main() {
    Matrix2d a;
    a << 1, 2,
            3, 4;
    MatrixXd b(2, 2);
    b << 2, 3,
            1, 4;
    cout << "a + b =\n" << a + b << endl;
    cout << "a - b =\n" << a - b << endl;
    cout << "Doing a += b;" << endl;
    a += b;
    cout << "Now a =\n" << a << endl;
    Vector3d v(1, 2, 3);
    Vector3d w(1, 0, 0);
    cout << "-v + w - v =\n" << -v + w - v << endl;
//////////// inverse matrix //////////////////
    Matrix3d m = Matrix3d::Random();
    Matrix3d n = m.inverse();
    cout << "Here is the matrix m:" << endl << m << endl;
    cout << "Its inverse is:" << endl << m.inverse() << endl;
    cout << "m*n" << endl << m * n << endl;

//// larger matrix   suh/////////////
    MatrixXd d34(3, 4);
    d34 << 2, 3, 4, 5,
            0, -1, 1, 1,
            1, 4, 0, 0;
    cout << " d " << endl << d34 << endl;
    //cout << " 2d " << endl << 2 * d34 << endl;
    MatrixXd e43(4, 3);
    e43 << 2, 3, 4,
            5, 0, -1,
            1, 1, 1,
            4, 0, 0;

    MatrixXd f = d34 * e43;
    cout << "e43\n" << e43 << endl << " f \n" << f << endl;

//////  array of VectorXd /////
    VectorXd *xX = new VectorXd[10];
    for (int i = 0; i < 10; i++) {
        xX[i] = VectorXd(4);
        for (int j = 0; j < 4; j++) { xX[i][j] = i + j; }
        cout << endl << endl << xX[i] << endl;
    }
    ///   orthonormal ///
    xX[0] << 0.5, 0.5, 0.5, 0.5;
    xX[1] << 0.5, 0.5, -0.5, -0.5;
    xX[2] << 0.5, -0.5, -0.5, 0.5;
    xX[3] << 0.5, -0.5, 0.5, -0.5;
    cout << endl;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) { cout << xX[i].dot(xX[j]) << "  "; }
        cout << endl;
    }

    getchar();
    return 0;
}

