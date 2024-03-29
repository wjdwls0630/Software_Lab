//////////////////////////////////////////////////// 
//   2D convolution
//   Author: Doug Young Suh
//   Date  : Oct. 25, 2019
////////////////////////////////////////////////////
#include "stdafx.h"
#include <iostream>
#include <eigen/Dense>
#include <eigen/LU>

using namespace Eigen;
using namespace std;

template<typename Derived, typename Derived2>
Derived conv2d(const MatrixBase<Derived> &I, const MatrixBase<Derived2> &kernel);

int main() {
    const int M = 8;
    Matrix<double, M, M> im;
    for (int i = 0; i < M; i++)
        for (int j = 0; j < M; j++) im.coeffRef(i, j) = j;
    cout << "im \n" << im << endl;

    Matrix<double, 3, 3> filter;
    filter << -1, 0, 1,
            -1, 0, 1,
            -1, 0, 1;

    Matrix<double, 8, 8> O = conv2d(im, filter);
    cout << "O \n" << O << endl;
    getchar();
}

/////////////////////////////////////////////////////////////
//      2D convolution
//      I : input image     kernel : filter
//      return : convolved output matrix
//
//      Side areas aer set to be zero. 
/////////////////////////////////////////////////////////////
template<typename Derived, typename Derived2>
Derived conv2d(const MatrixBase<Derived> &I, const MatrixBase<Derived2> &kernel) {
    Derived O = Derived::Zero(I.rows(), I.cols());

    typedef typename Derived::Scalar Scalar;
    typedef typename Derived2::Scalar Scalar2;

    int col = 0, row = 0;
    int KSizeX = kernel.rows();
    int KSizeY = kernel.cols();

    int limitRow = I.rows() - KSizeX;
    int limitCol = I.cols() - KSizeY;

    Derived2 block;
    Scalar normalization = kernel.sum();
    if (normalization < 1E-6) {
        normalization = 1;
    }
    for (row = KSizeX; row < limitRow; row++) {

        for (col = KSizeY; col < limitCol; col++) {
            Scalar b = (static_cast<Derived2>(I.block(row, col, KSizeX, KSizeY)).cwiseProduct(kernel)).sum();
            O.coeffRef(row, col) = b;
        }
    }

    return O / normalization;
}