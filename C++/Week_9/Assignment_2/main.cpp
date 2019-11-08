//
// Created by ParkJungJin on 2019-10-29.
//

#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <boost/math/special_functions/binomial.hpp>


//unsigned long long factorial(int n);

double poisson(double alpha, int x);

double binomialCoeff(int n, int k);

double binomial(int n, double p, int x);

int main() {

    //file record
    std::ofstream out("data.txt", std::ios::out);

    //value
    double p = 0.1, alpha;

    //container
    std::vector<std::vector<double>> binomial_list;
    std::vector<std::vector<double>> poisson_list;
    std::vector<int> n_list;
    std::vector<double> temp1;
    std::vector<double> temp2;
    int try_order = 1;
    int num_try_avg = 1000;

    for (int n = 10; n <= 1000; n *= 10, try_order++) {
        //init
        alpha = n * p;
        out << 'n' << ' ' << n << '\n';

        for (int x = 0; x <= n; x++) {
            temp1.push_back(binomial(n, p, x));
            temp2.push_back(poisson(alpha, x));
        }

        //make average

        for (int i = 1; i < num_try_avg; i++) {
            for (int x = 0; x < n; x++) {
                temp1[x] += binomial(n, p, x);
                temp2[x] += poisson(alpha, x);
            }
        }

        for (int i = 0; i < temp1.size(); i++) {
            temp1[i] /= num_try_avg;
            temp2[i] /= num_try_avg;
        }

        out << "binomial" << '\n';
        for (int i = 0; i < temp1.size(); i++) {
            out << i << ' ' << temp1[i] << '\n';
        }
        out << '\n';

        out << "poisson" << '\n';
        for (int i = 0; i < temp2.size(); i++) {
            out << i << ' ' << temp2[i] << '\n';
        }

        out << '\n';

        //record in vector
        binomial_list.push_back(temp1);
        poisson_list.push_back(temp2);

        //reset
        temp1.clear();
        temp2.clear();
    }
    return 1;
}

/*
unsigned long long factorial(int n){

    //tail recursive
    if (n == 0){
        return 1; //escape case
    }
    return n*factorial(n-1);

    if(n==0){
        return 1;
    }

    unsigned long long result = 1;
    for (int i = 0; i <= n; i++) {
        result *= i;
    }
    return result;
}
*/

double poisson(double alpha, int x) {
    double result = 1.0;
    for (int i = 1; i <= x; i++) {
        result *= (alpha / double(i));
    }
    return result * exp(-alpha);
}

// Returns value of Binomial Coefficient C(n, k)
double binomialCoeff(int n, int k) {
    double result = 1.0;
    for (int i = 1; i <= k; i++) {
        result *= (double) (n - k + i) / i;
    }
    return result;
}

double binomial(int n, double p, int x) {
    //return boost::math::binomial_coefficient<double>(n, x)*pow(p, x)*pow((1-p), (n-x));
    return binomialCoeff(n, x) * pow(p, x) * pow((1 - p), (n - x));
}