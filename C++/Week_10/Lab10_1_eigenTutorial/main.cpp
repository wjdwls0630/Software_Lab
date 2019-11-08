//
// Created by ParkJungJin on 2019-09-30.
//

#include <iostream>
#include <random>
#include <Eigen/Dense>

int main() {
    Eigen::Matrix2d a;
    a << 1, 2,
            3, 4;
    Eigen::MatrixXd b(2, 2);
    b << 2, 3,
            1, 4;
    std::cout << "a + b =\n" << a + b << '\n';
    std::cout << "a - b =\n" << a - b << '\n';
    std::cout << "Doing a += b;" << '\n';
    a += b;
    std::cout << "Now a =\n" << a << '\n';
    Eigen::Vector3d v(1, 2, 3);
    Eigen::Vector3d w(1, 0, 0);
    std::cout << "-v + w - v =\n" << -v + w - v << '\n';
//////////// inverse matrix //////////////////
    Eigen::Matrix3d m = Eigen::Matrix3d::Random();
    Eigen::Matrix3d n = m.inverse();
    std::cout << "Here is the matrix m:" << '\n' << m << '\n';
    std::cout << "Its inverse is:" << '\n' << m.inverse() << '\n';
    std::cout << "m*n" << '\n' << m * n << '\n';

//// larger matrix   suh/////////////
    Eigen::MatrixXd d34(3, 4);
    d34 << 2, 3, 4, 5,
            0, -1, 1, 1,
            1, 4, 0, 0;
    std::cout << " d " << '\n' << d34 << '\n';
    //std::cout << " 2d " << '\n << 2 * d34 << '\n;
    Eigen::MatrixXd e43(4, 3);
    e43 << 2, 3, 4,
            5, 0, -1,
            1, 1, 1,
            4, 0, 0;

    Eigen::MatrixXd f = d34 * e43;
    std::cout << "e43\n" << e43 << '\n' << " f \n" << f << '\n';

//////  array of Eigen::VectorXd /////
    Eigen::VectorXd *xX = new Eigen::VectorXd[10];
    for (int i = 0; i < 10; i++) {
        xX[i] = Eigen::VectorXd(4);
        for (int j = 0; j < 4; j++) { xX[i][j] = i + j; }
        std::cout << '\n' << '\n' << xX[i] << '\n';
    }
    ///   orthonormal ///
    xX[0] << 0.5, 0.5, 0.5, 0.5;
    xX[1] << 0.5, 0.5, -0.5, -0.5;
    xX[2] << 0.5, -0.5, -0.5, 0.5;
    xX[3] << 0.5, -0.5, 0.5, -0.5;
    std::cout << '\n';
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) { std::cout << xX[i].dot(xX[j]) << "  "; }
        std::cout << '\n';
    }

    getchar();
    return 0;
}

