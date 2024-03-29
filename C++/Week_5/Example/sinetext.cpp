// sinetext.cpp: 콘솔 응용 프로그램의 진입점을 정의합니다.
//
#include "stdafx.h"
#include <fstream>
#include <iostream>

#define PI 3.141592
using namespace std;


int main() {
    ofstream myout("mytext.txt");
    float sint, t, dt, T;
    dt = 1. / 8000.;
    T = 10. / 220.; // 10 periods
    for (t = 0; t < T; t += dt) {
        sint = 3. * sin(2 * PI * 220 * t);
        myout << t << " " << sint << "\n";
    }
    myout.close();
    return 0;
}

