//
// Created by ParkJungJin on 2019-11-13.
//
#include "gaussElimination_jin.hpp"

int gaussElimination_jin(Eigen::MatrixXd &A, Eigen::VectorXd &B) {
    double aij, aii;
    for (int i = 0; i < A.rows(); ++i) {
        aii = A.diagonal(0)(i);
        if (aii == 0.0) {
            return -1;
        }

        //make ith row in ith cols to 1
        A.row(i) /= aii;
        B(i) /= aii;

        //to make all 0 ith row and the ith columns
        for (int j = 0; j < A.cols(); j++) {
            if (i != j) {
                aij = A.col(i)(j);
                A.row(j) -= aij * A.row(i);
                B(j) -= aij * B(i);
            }
        }
    }
    return 1;
}

