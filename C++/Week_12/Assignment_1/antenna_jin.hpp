//
// Created by ParkJungJin on 2019-11-21.
//

#ifndef _ANTENNA_JIN_HPP
#define _ANTENNA_JIN_HPP

#include <iostream>
#include <cmath>
#include <fstream>

#define C 3e8 // velocity of light (m/s)
#define I0 40

class antenna_jin {
private:
    //EM parameter
    double f; //frequency
    double w; // angular frequency
    double k; // w/c
    double T; //period

    //time parameter (t) (unit : s)
    double N_t; //number of samples in time domain
    double end_time; // end_time of wave
    double start_time; // start_time of wave
    double dt;  // step of time


    //location parameter (r) (unit : m)
    double N_r; // number of samples in r domain

    double end_r; // end point of wave (m)
    double start_r; // start point of wave
    double dr; // step of location


    //container
    double *Rxt_plus, *Rxt, *Rxt_minus;

    //output file
    std::ofstream outFile;


public:
    antenna_jin(double f = 10e6);

    virtual ~antenna_jin();

    void calculate();

    int write2File(int tn);
};


#endif //WEEK_11_ASSIGNMENT_1_ANTENNA_JIN_HPP
