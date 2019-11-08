//
// Created by ParkJungJin on 2019-10-29.
//

#include <iostream>
#include <random>
#include <fstream>

#define NTRY 100000
#define MAXSUM 600

int main() {

    //file record
    std::ofstream out("data.txt", std::ios::out);

    //for random
    std::random_device rd;
    std::mt19937_64 rng(rd());
    std::uniform_int_distribution<int> dist(1, 6);

    //value
    double mean, var, dev;
    int sum = 0;
    int *hits_list;

    for (int k = 10; k <= 100000; k *= 10) {
        //init
        hits_list = new int[600]{0,};

        for (int n = 0; n < k; n++) {
            //initialize
            sum = 0;
            for (int i = 0; i < 100; i++) {
                sum += dist(rng);
            }
            hits_list[sum - 1]++;
        }

        //record
        std::cout << "n = " << k << '\n';
        out << 'n' << ' ' << k << '\n';

        //init
        mean = 0.0;
        var = 0.0;

        for (int a = 0; a < 600; a++) {
            //record
            out << a + 1 << ' ' << (double) hits_list[a] / k << '\n';

            //mean
            mean += (a + 1) * ((double) hits_list[a] / k);

            //var
            var += pow((a + 1), 2) * ((double) hits_list[a] / k);
        }
        std::cout << "mean : " << mean << '\t';
        out << mean << ' ';
        var -= pow(mean, 2);
        dev = sqrt(var);
        std::cout << "var : " << var << '\t';
        out << var << ' ';
        std::cout << "dev : " << dev << '\n';
        out << dev << '\n' << '\n';

        delete[] hits_list;
    }




    //calculate mean and standard deviation
    //mean

    return 1;
}

