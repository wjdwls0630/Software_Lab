//
// Created by ParkJungJin on 2019-09-30.
//

#include <iostream>
#include <random>

int main() {
    //for random
    std::random_device rd;
    std::mt19937_64 rng(rd());
    std::uniform_real_distribution<double> dist(0, 1);

    double pa = 12.3, pb = 26.5, pc = 17.23, pd = 22.3, pe = 9.2, pf = 12.47;
    double Pa, Pb, Pc, Pd, Pe, Pf;
    Pa = pa;
    Pb = Pa + pb;
    Pc = Pb + pc;
    Pd = Pc + pd;
    Pe = Pd + pe;
    Pf = Pe + pf;

    double x;
    double *hits_list;

    for (int n = 1; n < 100000; n *= 10) {
        //init list
        hits_list = new double[6]{0,};
        for (int i = 0; i < n; i++) {
            x = dist(rng) * pow(10, 2);
            if (x < Pa) {
                hits_list[0]++;
            } else if (x < Pb) {
                hits_list[1]++;
            } else if (x < Pc) {
                hits_list[2]++;
            } else if (x < Pd) {
                hits_list[3]++;
            } else if (x < Pe) {
                hits_list[4]++;
            } else {
                hits_list[5]++;
            }
        }
        std::cout << "n = " << n << '\n';
        std::cout << "hits_pa : " << hits_list[0] / n * pow(10, 2) << '\n';
        std::cout << "hits_pb : " << hits_list[1] / n * pow(10, 2) << '\n';
        std::cout << "hits_pc : " << hits_list[2] / n * pow(10, 2) << '\n';
        std::cout << "hits_pd : " << hits_list[3] / n * pow(10, 2) << '\n';
        std::cout << "hits_pe : " << hits_list[4] / n * pow(10, 2) << '\n';
        std::cout << "hits_pf : " << hits_list[5] / n * pow(10, 2) << '\n';
        std::cout << '\n';
        delete[] hits_list;
    }


    return 1;
}

