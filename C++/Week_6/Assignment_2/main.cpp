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
#include <chrono>

using ns = std::chrono::nanoseconds;
using get_time = std::chrono::steady_clock;

double gaussian(double x, double y, double mux, double muy, double sigx, double sigy, double peak);

double fxy(const double &x, const double &y);

double dfxydx(const double &x, const double &y, const double &dx);

double dfxydy(const double &x, const double &y, const double &dy);

double distance(double x0, double y0, double x1, double y1);

void ascend(double &x0, double &y0, double &x1, double &y1, const double &dx, const double &dy, double psi);

void descend(double &x0, double &y0, double &x1, double &y1, const double &dx, const double &dy, double psi);

int equal(std::vector<double> &v1, std::vector<double> &v2);

bool compare_fxy(std::vector<double> &v1, std::vector<double> &v2);

int compare(std::vector<double> &temp, std::vector<std::vector<double>> &local_list);

double cal_accuracy(double x);

int main() {
    //file open
    std::ofstream out("data.txt", std::ios::out);
    std::ofstream out_log("data_log.txt", std::ios::out);
    std::ofstream out_log_coord("data_log_coord.txt", std::ios::out);
    std::ofstream out_pe("data_pe.txt", std::ios::out);

    if (!out) {
        std::cerr << "Cannot open data.txt file" << '\n';
        return -1;
    }

    //question 1 - show that the local minimums dependent of starting point

    //set variable

    // psi is step size, eta is precision
    double psi, eta;

    //set psi 0.01 eta 10^-9
    psi = pow(10, -2);
    eta = pow(10, -6);

    double dx, dy, xi0, xi1, yi0, yi1, x_init, y_init;

    //set dx=dy=0.001
    dx = dy = pow(10, -3);

    //set initial xi0, yi0
    xi0 = yi0 = 0;

    //local maximum_list
    std::vector<std::vector<double>> local_list;

    //iter_count
    int iter_count = 0;
    int iter_count_1 = 0;

    //store value calculate optimization
    std::vector<double> temp(3);
    temp = {0, 0, 0};

    //for random starting point
    std::random_device rd;
    std::mt19937_64 rng(rd());
    std::uniform_real_distribution<double> dist(-3, 3);

    //process start
    while (iter_count < 100000) {
        xi1 = dist(rng);
        yi1 = dist(rng);
        x_init = xi1;
        y_init = yi1;

        //find local maximum
        while (distance(xi0, yi0, xi1, yi1) > eta && iter_count_1 < 10000) {
            ascend(xi0, yi0, xi1, yi1, dx, dy, psi);
            iter_count_1++;
        }

        if (xi1 > -3 && xi1 < 3) {
            if (yi1 > -3 && yi1 < 3) {
                temp[0] = xi1;
                temp[1] = yi1;
                temp[2] = fxy(xi1, yi1);

                if (compare(temp, local_list)) {
                    // if compare is 1, record how to move it
                    out_log << x_init << '\t' << y_init << "\t->\t";
                    out_log_coord << x_init << ' ' << y_init << ' ' << fxy(x_init, y_init) << ' ';
                    out_log << xi1 << '\t' << yi1 << '\n';
                    out_log_coord << xi1 << ' ' << yi1 << ' ' << fxy(xi1, yi1) << '\n';
                }
            }
        }
        iter_count++;
    }

    /*
     * question 2 - discuss quantitative analysis of cost/benefit(accuracy vs number of iterations)
     * with respect to eta and psi
     */

    //set variable

    //set psi start 1
    psi = 1;

    //order of psi and eta
    int psi_order = 0;
    int eta_order = 0;

    //accuracy, time
    double time = 0;
    double accuracy = 0;

    //iter count
    iter_count = 0;

    //case 1 (-1, -1, 2)
    std::vector<double> local_1(3);
    local_1 = {-1, -1, 2};

    //case 2 (1, 1, 4)
    std::vector<double> local_2(3);
    local_2 = {1, 1, 4};

    //iter_count


    for (int i = 0; i < 6; ++i) {
        psi *= pow(10, -1);
        psi_order++;
        for (int j = 0; j < 8; ++j) {
            eta *= pow(10, -1);
            eta_order++;
            //find local maximum
            //set initial xi0, yi0
            xi0 = yi0 = 0;

            //process optimization

            xi1 = 0.1;
            yi1 = 0.1;

            //find local maximum
            //time record
            auto start = get_time::now();
            while (distance(xi0, yi0, xi1, yi1) > eta && iter_count < 1000) {
                ascend(xi0, yi0, xi1, yi1, dx, dy, psi);
            }
            auto end = get_time::now();
            auto time_diff = end - start;
            time = std::chrono::duration_cast<ns>(time_diff).count() * pow(10, -6);

            if (xi1 > -3 && xi1 < 3) {
                if (yi1 > -3 && yi1 < 3) {
                    temp[0] = xi1;
                    temp[1] = yi1;
                    temp[2] = fxy(xi1, yi1);

                    //choose closer local point
                    if (abs(temp[2] - local_1[2]) < abs(temp[2] - local_2[2])) {
                        //if temp is closer to (-1, -1, 2)
                        accuracy = cal_accuracy(distance(temp[0], local_1[0], temp[1], local_1[1]));

                    } else {
                        accuracy = cal_accuracy(distance(temp[0], local_2[0], temp[1], local_2[1]));
                    }

                    out_pe << psi_order << ' ' << eta_order << ' ' << accuracy << ' ' << time << '\n';
                }
            }

        }
        //reset
        eta = 1;
        eta_order = 0;

        iter_count = 0;
    }




    //file record

    //set dx=dy =0.01 for using python graph
    dx = dy = 0.1;
    out << std::setw(20) << " ";
    for (double x = -3; x < 3; x += dx) {
        out << std::setw(20) << x;
    }
    out << '\n';

    for (double y = -3; y < 3; y += dy) {
        out << std::setw(20) << y;
        for (double x = -3; x < 3; x += dx) {
            out << std::setw(20) << fxy(x, y);
        }
        out << '\n';
    }

    std::ofstream out_local("data_local.txt", std::ios::out);

    std::sort(local_list.begin(), local_list.end());
    for (int i = 0; i < local_list.size(); ++i) {
        for (int j = 0; j < local_list[i].size(); ++j) {
            out_local << local_list[i][j] << ' ';
        }
        out_local << '\n';
    }

    out.close();
    out_local.close();
    out_log.close();

    return 1;

}

double gaussian(double x, double y, double mux, double muy, double sigx, double sigy, double peak) {
    return (peak * exp(-pow((x - mux) / sigx, 2.0) - pow((y - muy) / sigy, 2.0)));
}


double fxy(const double &x, const double &y) {
    return gaussian(x, y, 1.0, 1.0, 1.0, 2.0, 4.0) + gaussian(x, y, -1.0, -1.0, 1.0, 1.0, 2.0);
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

void ascend(double &x0, double &y0, double &x1, double &y1, const double &dx, const double &dy, double psi) {
    x0 = x1;
    y0 = y1;
    x1 += psi * dfxydx(x0, y0, dx);
    y1 += psi * dfxydy(x0, y0, dy);
}

void descend(double &x0, double &y0, double &x1, double &y1, const double &dx, const double &dy, double psi) {
    x0 = x1;
    y0 = y1;
    x1 -= psi * dfxydx(x0, y0, dx);
    y1 -= psi * dfxydy(x0, y0, dy);

}

int equal(std::vector<double> &v1, std::vector<double> &v2) {
    double interval = pow(10, -6);
    if (abs(v1[0] - v2[0]) > interval) {
        return 0;
    }

    if (abs(v1[1] - v2[1]) > interval) {
        return 0;
    }

    if (abs(v1[2] - v2[2]) > interval) {
        return 0;
    }

    return 1;
}

bool compare_fxy(std::vector<double> &v1, std::vector<double> &v2) {
    return v1[v1.size() - 1] < v2[v2.size() - 1];
}

int compare(std::vector<double> &temp, std::vector<std::vector<double>> &local_list) {
    if (local_list.size() == 0) {
        local_list.push_back(temp);
        return 1;
    } else if (local_list.size() == 1) {
        if (!equal(temp, local_list[0])) {
            local_list.push_back(temp);
        }
        return 1;

    } else if (local_list.size() >= 2) {
        //all complete, func has only 2 local maximum point
        //sort
        std::sort(local_list.begin(), local_list.end(), (compare_fxy));

        //case 1 (-1, -1, 2)
        if (abs(temp[2] - 2) < pow(10, -1)) {
            if (abs(temp[0] + 1) < pow(10, -1) && abs(temp[1] + 1) < pow(10, -1)) {
                if (!equal(temp, local_list[0])) {
                    local_list.push_back(temp);
                }
                return 1;
            }
        }
            //case 2 (1, 1, 4)
        else if (abs(temp[2] - 4) < pow(10, -1)) {
            if (abs(temp[0] - 1) < pow(10, -1) && abs(temp[1] - 1) < pow(10, -1)) {
                if (!equal(temp, local_list[1])) {
                    local_list.push_back(temp);
                }
                return 1;
            }
        }
    }
    //if there is no matched condition, don't record
    return 0;
}

double cal_accuracy(double x) {
    return (1 - (abs(x - pow(10, -8)) / x)) * pow(10, 4);
}