//
// Created by ParkJungJin on 2019-09-22.
//

#include <iostream>
#include <iomanip>
#include <fstream>
#include <cmath>

float fxy(float x, float y);

float dfxydx(float x, float y, float dx);

float dfxydy(float x, float y, float dy);

float distance(float x0, float y0, float x1, float y1);

void integration(float dt);

int main() {
    //file open
    std::ofstream out("data.txt", std::ios::out);

    if (!out) {
        std::cerr << "Cannot open data.txt file" << '\n';
        return -1;
    }
    float psi = 0.1, eta = 0.001; //psi = 0.1 , 1 case
    // psi is step size, eta is precision
    float dx, dy, xi0, xi1, yi0, yi1;
    dx = dy = 0.1;
    xi0 = yi0 = 1;
    xi1 = yi1 = 2;


    int iter_count = 0;
    while ((distance(xi0, yi0, xi1, yi1) > eta) && (iter_count < 100)) {
        xi0 = xi1;
        yi0 = yi1;
        xi1 -= psi * dfxydx(xi0, yi0, dx);
        yi1 -= psi * dfxydy(xi0, yi0, dy);
        std::cout << std::setw(20) << xi0 << std::setw(20) << yi0 << " >> " << std::setw(20) << xi1 << std::setw(20)
                  << yi1 << '\n';
        iter_count++;
    }

    out << std::setw(20) << " ";
    for (float x = 1; x < 5; x += dx) {
        out << std::setw(20) << x;
    }
    out << '\n';

    for (float y = -4; y < 0; y += dy) {
        out << std::setw(20) << y;
        for (float x = 1; x < 5; x += dx) {
            out << std::setw(20) << fxy(x, y);
        }
        out << '\n';
    }


    std::cout << "iter_" << iter_count << " Distance = " << distance(xi0, yi0, xi1, yi1) << '\n';


    return 1;

}


float fxy(float x, float y) {
    return pow((x - 3), 2) + pow((y + 2), 2);
}

float dfxydx(float x, float y, float dx) {
    return (fxy((x + dx), y) - fxy(x, y)) / dx;

}

float dfxydy(float x, float y, float dy) {
    return (fxy(x, y + dy) - fxy(x, y)) / dy;
}

float distance(float x0, float y0, float x1, float y1) {
    return sqrt(pow(x0 - x1, 2) + pow(y0 - y1, 2));

}