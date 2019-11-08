//
// Created by ParkJungJin on 2019-09-22.
//

#include <iostream>
#include <iomanip>
#include <fstream>
#include <cmath>

float Vo = 100, a = 1, b = 2;

float Vxy(float &x, float &y);

int main() {
    float x = 0, y = 0, dx, dy;
    dx = dy = 0.1;

    //file open
    std::ofstream out("data.txt", std::ios::out);
    if (!out) {
        std::cerr << "Cannot open data.txt file" << '\n';
        return -1;
    }

    out << " " << std::setw(10);
    for (x = 0; x < b; x += dx) {
        out << x << std::setw(10) << '\n';
    }

    for (y = 0; y < a; y += dy) {
        out << y << '\n';
        for (x = 0; x < b; x += dx) {
            out << Vxy(x, y) << std::setw(10) << '\n';
        }
    }

    out.close();

    return 0;
}

float Vxy(float &x, float &y) {
    float sum = 0;
    for (int n = 1; n < 20; n += 2) {
        sum += sin(n * M_PI * x / b) * sinh(n * M_PI * y / b) / (n * sinh(n * M_PI * a / b));
    }
    sum *= Vo / M_PI;
    return sum;
}