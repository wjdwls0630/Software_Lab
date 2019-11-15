//
// Created by ParkJungJin on 2019-10-29.
//

#include <iostream>
#include <fstream>
#include <cmath>
#include "../gaussElimination_jin/gaussElimination_jin.hpp"

using ns = std::chrono::nanoseconds;
using get_time = std::chrono::steady_clock;

int GaussElimination(int N, float *a, float *b);

int main() {
    //eigen gaussian
    //eigen gaussian

    // data generation
    float dataX[100], dataY[100];
    int N = 0; //# of data
    std::ifstream datae("datae.txt");
    datae >> N;
    for (int i = 0; i < N; i++) {
        datae >> dataX[i] >> dataY[i];
    }
    datae.close();

    //data generation eigen gaussian
    double sum_x = 0, sum_y = 0, sum_xy = 0, sum_x_pow2 = 0;

    double tempX, tempY;
    /*
    for (int i = 0; i < N; i++) {
        if(dataY[i]<0){
            dataY[i]=;
        }
        tempX = dataX[i];
        sum_x += tempX;
        sum_x_pow2 += pow(tempX, 2);
        tempY = log(dataY[i]);
        sum_y += tempY;
        sum_xy += tempX*tempY;
    }
     */

    for (int i = 0; i < N; i++) {
        tempX = dataX[i];
        sum_x += tempX;
        sum_x_pow2 += pow(tempX, 2);
        if (dataY[i] < 0) {
            tempY = 0;
        } else {
            tempY = log(dataY[i]);
        }

        sum_y += tempY;
        sum_xy += tempX * tempY;
    }

    Eigen::MatrixXd A(2, 2);
    Eigen::VectorXd B(2);
    A << sum_x, N,
            sum_x_pow2, sum_x;
    B << sum_y, sum_xy;

    Eigen::MatrixXd tempA(2, 2);
    Eigen::VectorXd tempB(2);
    tempA = A;
    tempB = B;
    std::cout << "eigen gaussian" << '\n';
    auto start = get_time::now();
    gaussElimination_jin(tempA, tempB);
    auto end = get_time::now();
    auto time_diff = end - start;
    std::cout << "y = " << exp(tempB(1)) << "e^(" << tempB(0) << "x)" << '\n';
    std::cout << "computation time : " << std::chrono::duration_cast<ns>(time_diff).count() * pow(10, -3) << "us"
              << '\n';

    // example code array


    // LSM
    float a[4], b[2], c[2];
    for (int i = 0; i < 4; i++) a[i] = 0.0;
    for (int i = 0; i < 2; i++) b[i] = c[i] = 0.0;
    a[0] = sum_x;
    a[1] = N;
    b[0] = sum_y;
    a[2] = sum_x_pow2;
    a[3] = sum_x;
    b[1] = sum_xy;

    std::cout << "example code array gaussian" << '\n';

    start = get_time::now();
    GaussElimination(2, a, b);
    end = get_time::now();
    time_diff = end - start;
    std::cout << "y = " << exp(b[1]) << "e^(" << b[0] << "x)" << '\n';
    std::cout << "computation time : " << std::chrono::duration_cast<ns>(time_diff).count() * pow(10, -3) << "us"
              << '\n';

    //eigen function Solving linear least squares systems

    /*Of these, the SVD decomposition is generally the most accurate but the slowest,
     * normal equations is the fastest but least accurate,
     * and the QR decomposition is in between.
     */

    //Using the SVD decomposition
    std::cout << "Using the SVD decomposition" << '\n';
    start = get_time::now();
    tempB = A.bdcSvd(Eigen::ComputeThinU | Eigen::ComputeThinV).solve(B);
    end = get_time::now();
    time_diff = end - start;
    std::cout << "y = " << exp(tempB(1)) << "e^(" << tempB(0) << "x)" << '\n';
    std::cout << "computation time : " << std::chrono::duration_cast<ns>(time_diff).count() * pow(10, -3) << "us"
              << '\n';

    //Using the QR decomposition

    //HouseholderQR (no pivoting, so fast but unstable)
    std::cout << "HouseholderQR (no pivoting, so fast but unstable)" << '\n';
    start = get_time::now();
    tempB = A.householderQr().solve(B);
    end = get_time::now();
    time_diff = end - start;
    std::cout << "y = " << exp(tempB(1)) << "e^(" << tempB(0) << "x)" << '\n';
    std::cout << "computation time : " << std::chrono::duration_cast<ns>(time_diff).count() * pow(10, -3) << "us"
              << '\n';

    //ColPivHouseholderQR (column pivoting, thus a bit slower but more accurate)
    std::cout << "ColPivHouseholderQR (column pivoting, thus a bit slower but more accurate)" << '\n';
    start = get_time::now();
    tempB = A.colPivHouseholderQr().solve(B);
    end = get_time::now();
    time_diff = end - start;
    std::cout << "y = " << exp(tempB(1)) << "e^(" << tempB(0) << "x)" << '\n';
    std::cout << "computation time : " << std::chrono::duration_cast<ns>(time_diff).count() * pow(10, -3) << "us"
              << '\n';

    //FullPivHouseholderQR (full pivoting, so slowest and most stable)
    std::cout << "FullPivHouseholderQR (full pivoting, so slowest and most stable)" << '\n';
    start = get_time::now();
    tempB = A.fullPivHouseholderQr().solve(B);
    end = get_time::now();
    time_diff = end - start;
    std::cout << "y = " << exp(tempB(1)) << "e^(" << tempB(0) << "x)" << '\n';
    std::cout << "computation time : " << std::chrono::duration_cast<ns>(time_diff).count() * pow(10, -3) << "us"
              << '\n';

    //Using normal equations
    /*
     * If the matrix A is ill-conditioned, then this is not a good method,
     * because the condition number of ATA is the square of the condition number of A.
     * This means that you lose twice as many digits using normal equation
     * than if you use the other methods.
     *
     */
    std::cout << "Using normal equations" << '\n';
    start = get_time::now();
    tempB = (A.transpose() * A).ldlt().solve(A.transpose() * B);
    end = get_time::now();
    time_diff = end - start;
    std::cout << "y = " << exp(tempB(1)) << "e^(" << tempB(0) << "x)" << '\n';
    std::cout << "computation time : " << std::chrono::duration_cast<ns>(time_diff).count() * pow(10, -3) << "us"
              << '\n';

    return 1;
}

int GaussElimination(int N, float *a, float *b) {
    float temp, aii, aji;
    int i, j, k;
    //showequation(N, a, b);
    for (i = 0; i < N; i++) {
        aii = a[i * N + i];
        if (aii == 0.0) return -1; // ����/�Ҵ� ���� �� �� �� ����
        // i-th row�� aii�� ��� ������
        for (k = i; k < N; k++) a[i * N + k] /= aii;
        b[i] /= aii;
        // �ٸ� row���� i��° ���� ��� 0���� �����
        for (j = 0; j < N; j++) {
            if (i != j) {
                aji = a[j * N + i];
                for (k = i; k < N; k++) a[j * N + k] -= a[i * N + k] * aji;
                b[j] -= b[i] * aji;
            }// if(i!=j)
        } // other rows
        //showequation(N, a, b);
    }
    return 0;
}
