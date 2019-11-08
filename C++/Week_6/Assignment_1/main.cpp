//
// Created by ParkJungJin on 2019-09-22.
//

#include <iostream>
#include <iomanip>
#include <fstream>
#include <cmath>
#include <vector>
#include <algorithm>
#include <random>

#define PSI 0.01

double fxy(const double &x, const double &y);

double dfxydx(const double &x, const double &y, const double &dx);

double dfxydy(const double &x, const double &y, const double &dy);

double distance(double x0, double y0, double x1, double y1);

void ascend(double &x0, double &y0, double &x1, double &y1, const double &dx, const double &dy);

void descend(double &x0, double &y0, double &x1, double &y1, const double &dx, const double &dy);

int check(std::vector<double> &temp, std::vector<std::vector<double>> &local_list);

int main() {
    //file open
    std::ofstream out("data.txt", std::ios::out);
    std::ofstream out_log("data_log.txt", std::ios::out);

    if (!out) {
        std::cerr << "Cannot open data.txt file" << '\n';
        return -1;
    }
    double psi = pow(10, -2), eta = pow(10, -9);
    // psi is step size, eta is precision
    double dx, dy, xi0, xi1, yi0, yi1, x_init, y_init;
    dx = dy = pow(10, -2);
    xi0 = yi0 = 0;
    xi1 = xi0 + dx;
    yi1 = yi0 + dy;

    std::vector<std::vector<double>> local_list;

    //local _list
    //x, y, fxy

    int iter_count = 0;
    int index = 0;

    std::vector<double> temp(3);
    temp = {0, 0, 0};
    std::random_device rd;
    std::mt19937_64 rng(rd());
    std::uniform_real_distribution<double> dist(0, 1);


    while (iter_count < 1000) {
        xi1 = dist(rng);
        std::cout << xi1 << '\n';
        yi1 = dist(rng);
        x_init = xi1;
        y_init = yi1;

        //find local maximum
        while (distance(xi0, yi0, xi1, yi1) > eta) {
            ascend(xi0, yi0, xi1, yi1, dx, dy);
        }

        if (xi1 > 0 && xi1 < 1) {
            if (yi1 > 0 && yi1 < 1) {
                temp[0] = xi1;
                temp[1] = yi1;
                temp[2] = fxy(xi1, yi1);
                if (check(temp, local_list)) {
                    local_list.push_back(temp);
                    out_log << x_init << '\t' << y_init << "\t->\t";
                    out_log << xi1 << '\t' << yi1 << '\n';
                }
            }
        }


        xi1 = dist(rng);
        std::cout << xi1 << '\n';
        yi1 = dist(rng);
        x_init = xi1;
        y_init = yi1;




        //find local minimum
        while (distance(xi0, yi0, xi1, yi1) > eta) {
            descend(xi0, yi0, xi1, yi1, dx, dy);
        }

        if (xi1 > 0 && xi1 < 1) {
            if (yi1 > 0 && yi1 < 1) {
                temp[0] = xi1;
                temp[1] = yi1;
                temp[2] = fxy(xi1, yi1);
                if (check(temp, local_list)) {
                    local_list.push_back(temp);
                    out_log << x_init << '\t' << y_init << "\t->\t";
                    out_log << xi1 << '\t' << yi1 << '\n';
                }
            }
        }
        iter_count++;
    }


    out << std::setw(20) << " ";
    for (double x = 0; x < 1; x += dx) {
        out << std::setw(20) << x;
    }
    out << '\n';

    for (double y = 0; y < 1; y += dy) {
        out << std::setw(20) << y;
        for (double x = 0; x < 1; x += dx) {
            out << std::setw(20) << fxy(x, y);
        }
        out << '\n';
    }

    std::ofstream out_local("data_local.txt", std::ios::out);

    std::sort(local_list.begin(), local_list.end());
    for (int i = 0; i < local_list.size(); ++i) {
        for (int j = 0; j < local_list[i].size(); ++j) {
            std::cout << local_list[i][j] << '\n';
            out_local << local_list[i][j] << ' ';
        }
        out_local << '\n';
    }

    out.close();
    out_local.close();
    out_log.close();

    return 1;

}


double fxy(const double &x, const double &y) {
    double f0 = 1., f1 = 2.;
    return sin(2. * M_PI * f0 * x) * sin(2. * M_PI * f1 * y);
}

double dfxydx(const double &x, const double &y, const double &dx) {
    return (fxy((x + dx / 2), y) - fxy((x - dx / 2), y)) / dx;

}

double dfxydy(const double &x, const double &y, const double &dy) {
    return (fxy(x, y + dy / 2) - fxy(x, y - dy / 2)) / dy;
}

double distance(double x0, double y0, double x1, double y1) {
    return sqrt(pow(x0 - x1, 2) + pow(y0 - y1, 2));
}

void ascend(double &x0, double &y0, double &x1, double &y1, const double &dx, const double &dy) {
    x0 = x1;
    y0 = y1;
    x1 += PSI * dfxydx(x0, y0, dx);
    y1 += PSI * dfxydy(x0, y0, dy);
}

void descend(double &x0, double &y0, double &x1, double &y1, const double &dx, const double &dy) {
    x0 = x1;
    y0 = y1;
    x1 -= PSI * dfxydx(x0, y0, dx);
    y1 -= PSI * dfxydy(x0, y0, dy);

}

int check(std::vector<double> &temp, std::vector<std::vector<double>> &local_list) {
    for (int i = 0; i < local_list.size(); ++i) {
        if (round(temp[0] * pow(10, 6)) / pow(10, 6) == round(local_list[i][0] * pow(10, 6)) / pow(10, 6)) {
            if (round(temp[1] * pow(10, 6)) / pow(10, 6) == round(local_list[i][1] * pow(10, 6)) / pow(10, 6)) {
                if (round(temp[2] * pow(10, 6)) / pow(10, 6) == round(local_list[i][2] * pow(10, 6)) / pow(10, 6)) {
                    return 0;
                }
            }
        }
    }
    return 1;
}