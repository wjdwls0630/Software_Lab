//
// Created by ParkJungJin on 2019-10-23.
//

#include <string>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include "../matrix_jin/matrix_jin.hpp"


int main() {
    //question 1

    std::cout << "---------------question 1---------------" << '\n';

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

    double *a1, *a2, *a3;
    a1 = new double[4]{100, -120, -4, 2};
    a2 = new double[4]{100, 20, 120, 32};
    a3 = new double[4]{10, 120, 108, 8};

    double **a_list;
    a_list = new double *[3]{a1, a2, a3};


    matrix_jin<double> a_matrix_list[3];
    for (int i = 0; i < 3; i++) {
        matrix_jin<double> temp(4, 1, "a" + std::to_string(i + 1), *(a_list++));
        *(a_matrix_list + i) = temp;
    }

    matrix_jin<double> A_matrix_list[3];
    for (int i = 0; i < 3; i++) {
        matrix_jin<double> temp = C * a_matrix_list[i];
        *(A_matrix_list + i) = temp;
        A_matrix_list[i].setName("A" + std::to_string(i + 1));
        A_matrix_list[i].showMatrix();

    }



    //question 2

    std::cout << "---------------question 2---------------" << '\n';

    matrix_jin<double> C_T(C);
    C_T.transpose();
    C_T.setName("C^T");
    C_T.showMatrix();

    matrix_jin<double> a_result_list[3];

    for (int i = 0; i < 3; i++) {
        matrix_jin<double> temp = C_T * A_matrix_list[i];
        *(a_result_list + i) = temp;
        a_result_list[i].setName("a" + std::to_string(i + 1) + " = (C^T*A" + std::to_string(i + 1) + ")");
        a_matrix_list[i].showMatrix();
        a_result_list[i].showMatrix();
    }

    //question 3

    std::cout << "---------------question 3---------------" << '\n';

    //set two smallest elements of A_matrix to be zero

    A_matrix_list[0][0] = 0;
    A_matrix_list[0][1] = 0;

    A_matrix_list[1][1] = 0;
    A_matrix_list[1][2] = 0;

    A_matrix_list[1][2] = 0;
    A_matrix_list[1][3] = 0;

    for (int i = 0; i < 3; i++) {
        a_result_list[i].showMatrix();
        matrix_jin<double> temp = C_T * A_matrix_list[i];
        *(a_result_list + i) = temp;
        a_result_list[i].setName("a" + std::to_string(i + 1) + " = (C^T*A" + std::to_string(i + 1) + ")(A set zero)");
        a_result_list[i].showMatrix();
    }

    //de allocate memory
    for (int i = 0; i < 4; i++) {
        delete[] *(c_list + i);
    }
    delete[] c_list;

    for (int i = 0; i < 4; i++) {
        delete[] *(a_list + i);
    }
    delete[] a_list;


    return 1;

}

