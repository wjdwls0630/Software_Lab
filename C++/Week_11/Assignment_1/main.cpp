//
// Created by ParkJungJin on 2019-10-29.
//

#include <iostream>
#include <fstream>
#include "../gaussElimination_jin/gaussElimination_jin.hpp"

using ns = std::chrono::nanoseconds;
using get_time = std::chrono::steady_clock;

int GaussElimination(int N, float *a, float *b);

int main() {
    //eigen gaussian

    // data generation
    float dataX[100], dataY[100];
    int N = 0; //# of data
    std::ifstream data2("data2.txt");
    data2 >> N;
    for (int i = 0; i < N; i++) {
        data2 >> dataX[i] >> dataY[i];
    }
    data2.close();

    double sum_x = 0, sum_x_pow2 = 0, sum_x_pow3 = 0, sum_x_pow4 = 0,
            sum_y = 0, sum_xy = 0, sum_x_pow2y = 0;

    double tempX, tempY;
    for (int i = 0; i < N; i++) {
        tempX = dataX[i];
        sum_x += tempX;
        sum_x_pow2 += pow(tempX, 2);
        sum_x_pow3 += pow(tempX, 3);
        sum_x_pow4 += pow(tempX, 4);
        tempY = dataY[i];
        sum_y += tempY;
        sum_xy += tempX * tempY;
        sum_x_pow2y += pow(tempX, 2) * tempY;
    }

    //eigen setting
    Eigen::MatrixXd A(3, 3);
    Eigen::VectorXd B(3);
    A << sum_x_pow2, sum_x, N,
            sum_x_pow3, sum_x_pow2, sum_x,
            sum_x_pow4, sum_x_pow3, sum_x_pow2;

    B << sum_y, sum_xy, sum_x_pow2y;

    Eigen::MatrixXd tempA(3, 3);
    Eigen::VectorXd tempB(3);
    tempA = A;
    tempB = B;
    std::cout << "eigen gaussian" << '\n';
    auto start = get_time::now();
    gaussElimination_jin(tempA, tempB);
    auto end = get_time::now();
    auto time_diff = end - start;
    std::cout << "y = " << tempB(0) << " x^2 + " << tempB(1) << " x + " << tempB(0) << "\n";
    std::cout << "computation time : " << std::chrono::duration_cast<ns>(time_diff).count() * pow(10, -3) << "us"
              << '\n';

    // example code array

    // LSM
    float a[9], b[3];
    for (int i = 0; i < 4; i++) a[i] = 0.0;
    for (int i = 0; i < 2; i++) b[i] = 0.0;

    a[0] = sum_x_pow2;
    a[1] = sum_x;
    a[2] = N;
    a[3] = sum_x_pow3;
    a[4] = sum_x_pow2;
    a[5] = sum_x;
    a[6] = sum_x_pow4;
    a[7] = sum_x_pow3;
    a[8] = sum_x_pow2;
    b[0] = sum_y;
    b[1] = sum_xy;
    b[2] = sum_x_pow2y;

    std::cout << "example code array gaussian" << '\n';

    start = get_time::now();
    GaussElimination(3, a, b);
    end = get_time::now();
    time_diff = end - start;
    std::cout << "y = " << b[0] << " x^2 + " << b[1] << "x +" << b[2] << "\n";
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
    std::cout << "y = " << tempB(0) << " x^2 + " << tempB(1) << " x + " << tempB(0) << "\n";
    std::cout << "computation time : " << std::chrono::duration_cast<ns>(time_diff).count() * pow(10, -3) << "us"
              << '\n';

    //Using the QR decomposition

    //HouseholderQR (no pivoting, so fast but unstable)
    std::cout << "HouseholderQR (no pivoting, so fast but unstable)" << '\n';
    start = get_time::now();
    tempB = A.householderQr().solve(B);
    end = get_time::now();
    time_diff = end - start;
    std::cout << "y = " << tempB(0) << " x^2 + " << tempB(1) << " x + " << tempB(0) << "\n";
    std::cout << "computation time : " << std::chrono::duration_cast<ns>(time_diff).count() * pow(10, -3) << "us"
              << '\n';

    //ColPivHouseholderQR (column pivoting, thus a bit slower but more accurate)
    std::cout << "ColPivHouseholderQR (column pivoting, thus a bit slower but more accurate)" << '\n';
    start = get_time::now();
    tempB = A.colPivHouseholderQr().solve(B);
    end = get_time::now();
    time_diff = end - start;
    std::cout << "y = " << tempB(0) << " x^2 + " << tempB(1) << " x + " << tempB(0) << "\n";
    std::cout << "computation time : " << std::chrono::duration_cast<ns>(time_diff).count() * pow(10, -3) << "us"
              << '\n';

    //FullPivHouseholderQR (full pivoting, so slowest and most stable)
    std::cout << "FullPivHouseholderQR (full pivoting, so slowest and most stable)" << '\n';
    start = get_time::now();
    tempB = A.fullPivHouseholderQr().solve(B);
    end = get_time::now();
    time_diff = end - start;
    std::cout << "y = " << tempB(0) << " x^2 + " << tempB(1) << " x + " << tempB(0) << "\n";
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
    std::cout << "y = " << tempB(0) << " x^2 + " << tempB(1) << " x + " << tempB(0) << "\n";
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
