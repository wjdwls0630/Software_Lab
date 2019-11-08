#include <iostream> // for cout 
#include <cstdlib>  // for rand( )
#include <conio.h>  // for getchar( )

#define PI 3.141592

using namespace std;

float factorial(float);

int main() {
    int hits[6], Ntry = 10000;
    int i, j;
    for (i = 0; i < 6; i++) hits[i] = 0;
    for (int i = 0; i < Ntry; i++) hits[rand() % 6]++;

    cout << "N = " << Ntry << " RAND_MAX = " << RAND_MAX << "\n\n";

    for (i = 0; i < 6; i++)
        cout << "P[" << i + 1 << "] = " << (float) hits[i] / Ntry << "\n\n";
    /////////  Monte-Carlo //////////////////
    float x, y, hit = 0.0;

    for (int i = 0; i < Ntry; i++) {
        x = (((float) rand() / (float) RAND_MAX) - 0.5) * 2.0;
        y = (((float) rand() / (float) RAND_MAX) - 0.5) * 2.0;
        if ((x * x + y * y) < 1.0) hit += 1.0;
    }
    cout << " PI = " << hit / Ntry * 4.0 << "\n\n";
    //////// srand( ) /////////////////
    srand(100);
    for (i = 0; i < 10; i++) cout << rand() << " ";
    cout << "\n";
    srand(100);
    for (i = 0; i < 10; i++) cout << rand() << " ";
    cout << "\n";
    srand(100);
    for (i = 0; i < 10; i++) cout << rand() << " ";
    cout << "\n";


    ///////// factorial(resursive) //////////
    cout << factorial(4.) << "\n\n";
    getchar();
    return 1;

    //// tetris /////
    float pa = 12.3, pb = 26.5, pc = 17.23, pd = 22.3, pe = 9.2, pf = 12.47;
    float Pa, Pb, Pc, Pd, Pe, Pf;
    Pa = pa;
    Pb = Pa + pb;
    Pc = Pb + pc;
    Pd = Pc + pd;
    Pe = Pd + pe;
    Pf = Pe + pf;
    x = (float) rand() / (float) RAND_MAX * 100.0;
    if (x < Pa) { ... }
    else(x < Pb)
    { ... }
    else(x < Pc)
    { ... }
    else(x < Pd)
    { ... }
    else(x < Pe)
    { ... }
    else       { ... }

}

float factorial(float n) {
    if (n > 0.0) return n * factorial(n - 1.0);
    else return 1.0;
}