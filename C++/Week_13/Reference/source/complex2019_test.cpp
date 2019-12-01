#include <iostream>
#include <complex>

using namespace std;

int main() {
    complex<double> z1(1, 2), z2, z3, zz[5];
    z2 = complex<double>(2, 3);
    z3 = z1 + z2;
    z1 = conj(z3);
    z2 = 3.0 * z1;
    cout << z3 << " conj " << z1 << " * 3 = " << z2 << endl;

    cout << "real " << real(z3) << endl;
    cout << "imag " << imag(z3) << endl;
    cout << "abs " << abs(z3) << endl;
    cout << "arg " << arg(z3) << endl;
    cout << "norm " << norm(z3) << endl;
    cout << "cos " << cos(z3) << endl;
    cout << "exp " << exp(z3) << endl;
    cout << "pow**2 " << pow(z3, 2) << endl;
    cout << "sqrt " << sqrt(z3) << " = " << pow(z3, 0.5) << endl;
    cout << " complex array \n";
    for (int i = 0; i < 5; i++) {
        zz[i] = complex<double>(i * 0.1, i * 10.0);
        cout << zz[i] << endl;
    }
    getchar();
    return 1;
}