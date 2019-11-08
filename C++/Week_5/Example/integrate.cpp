#include <iostream>
#include <conio.h>

#define g 9.8

using namespace std;

void calculate_x(float);

int main() {
    // integration
    float dt = 0.1;
    for (int i = 0; i < 5; i++) {
        calculate_x(dt);
        dt *= 0.1;
    }
    getchar();
    return 1;
}

void calculate_x(float ddt) {
    float t, T = 10, v, xbar, errorinpercent;
    xbar = 0.0;
    for (t = 0; t < T; t += ddt) {
        xbar += g * t * ddt;
    }
    errorinpercent = fabs(490. - xbar) / 490.0 * 100;
    cout << "dt " << ddt << " x=490 " << xbar << " error " << errorinpercent << "%\n";
}