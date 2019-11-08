//
// Created by ParkJungJin on 2019-09-22.
//

#include <iostream>
#include <iomanip>
#include <fstream>
#include <cmath>

#define g 9.8

void integration(float dt);

int main() {
    float dt = 1;

    for (int i = 0; i < 6; i++) {
        integration(dt);
        dt *= 0.1;
    }

    return 1;

}

void integration(float dt) {
    float x_bar = 0.;
    for (float t = 0; t < 10; t += dt) {
        x_bar += g * t * dt;
    }
    float ori_val = 0.5 * g * pow(10, 2);
    float errorinpercent = fabs((ori_val) - x_bar) / ori_val * 100;
    std::cout << "dt : " << dt << " ori_val : " << ori_val << " x_bar : " << x_bar << " error : " << errorinpercent
              << '\n';
}
