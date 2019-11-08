#include "stdafx.h"
#include "basis.h"

#define PI 3.141592

basis::basis(int n, int type) {
    c = VectorXd(n);
    float sqt = sqrt(2.0 / (double) n);
    if (type == 0)
        for (int i = 0; i < n; i++) {
            c[i] = sqt * cos(2 * PI * i / n);
        }
    else
        for (int i = 0; i < n; i++) {
            c[i] = sqt * sin(2 * PI * i / n);
        }
}