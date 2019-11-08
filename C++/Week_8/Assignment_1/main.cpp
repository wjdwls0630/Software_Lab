//
// Created by ParkJungJin on 2019-10-23.
//

#include <fstream>
#include <cstdlib>
#include <ctime>
#include "../matrix_jin/matrix_jin.hpp"


int main() {
    double *c0, *c1, *c2, *c3;
    c0 = new double[4]{1, 1, 1, 1};
    c1 = new double[4]{1, 1, -1, -1};
    c2 = new double[4]{1, -1, -1, 1};
    c3 = new double[4]{1, -1, 1, -1};

    double **c_list;
    c_list = new double *[4]{c0, c1, c2, c3};
    matrix_jin<double> C;
    C.setName("C");
    for (int i = 0; i < 4; i++) {
        C.appendRow(*(c_list++), 4, 1);
    }

    C.showMatrix();
    C.setName("C_Normalized");
    C.normalize();
    C.showMatrix();

    matrix_jin<double> C_T(C);
    C_T.transpose();
    C_T.setName("C^T");
    C_T.showMatrix();

    matrix_jin<double> CC_T = C * C_T;
    CC_T.setName("CC^T");
    CC_T.showMatrix();

    matrix_jin<double> C_Prime(C);
    C_Prime.swapRow(0, 2);
    C_Prime.setName("C'");
    C_Prime.showMatrix();

    matrix_jin<double> C_PrimeC_T = C_Prime * C_T;
    C_PrimeC_T.setName("C'C^T");
    C_PrimeC_T.showMatrix();
    return 1;

}

