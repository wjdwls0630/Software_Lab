#include <iostream>
#include <cmath>

using namespace std;

float fxy(float x, float y) { return (x - 3) * (x - 3) + (y + 2) * (y + 2); }

float dfxydx(float x, float y, float dx) { return (fxy(x + dx, y) - fxy(x, y)) / dx; }

float dfxydy(float x, float y, float dy) { return (fxy(x, y + dy) - fxy(x, y)) / dy; }

float EE(float x, float y, float x1, float y1) {
    return sqrt((x - x1) * (x - x1) + (y - y1) * (y - y1));
}

void main() {
    float psi = 0.03, eta = 0.001, dx = 0.05, dy = 0.05;
    float x0 = 2, x1 = 1, y0 = 2, y1 = 1;
    int iteration = 0;
    while (EE(x0, y0, x1, y1) > eta && iteration++ < 100) {
        x0 = x1;
        y0 = y1;
        x1 = x0 - psi * dfxydx(x0, y0, dx);
        y1 = y0 - psi * dfxydy(x0, y0, dy);
    }
    cout << iteration << "-th " << x1 << " " << y1 << endl;
    getchar();
}