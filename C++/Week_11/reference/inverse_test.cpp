#include <iostream>  // for IO
#include "myMatrix.h"

using namespace std;
#define NN 3

void main() {
    // ���� �Է��ϱ�
    float A[] = {2, -3, 4, 1, 0, 3, -2, 2, 1};
    float b[] = {-1, 5, 3};
    float IA[] = {1, 0, 0, 0, 1, 0, 0, 0, 1};
    if (GaussElimination(NN, A, b) == -1) {
        cout << "no solution.\n";
        exit(-1);
    }
    cout << " solution " << b[0] << "\t" << b[1] << "\t" << b[2] << "\n";
    getchar();
}