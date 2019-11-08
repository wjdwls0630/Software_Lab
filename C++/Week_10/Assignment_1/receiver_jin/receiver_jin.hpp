//
// Created by ParkJungJin on 2019-11-07.
//

#ifndef _RECEIVER_JIN_HPP
#define _RECEIVER_JIN_HPP

#include <iostream>
#include <fstream>
#include <cmath>
#include <Eigen/Dense>
#include "../file_stream/file_stream.hpp"

class receiver_jin {
private:
    int m_nbits;
    int m_nsamplespersymbol;
    int m_nbitspersymbol;
    int m_eb;
    double m_no;
    int m_nbit2Decimal;
    //corrupted signal with gaussian noise
    Eigen::MatrixXd m_corrupted_signal;
    Eigen::MatrixXd m_ct;
    Eigen::MatrixXd m_constellation;
    Eigen::MatrixXi m_decoded_data;

public:
    receiver_jin(int mNbits, int mNsamplespersymbol, int mNbitspersymbol, int mEb, double mNo);

    void demodulate();

    void receiveData();

    Eigen::MatrixXi decimal2Binary(int n);
};


#endif //_RECEIVER_JIN_HPP
