//
// Created by ParkJungJin on 2019-11-07.
//

#ifndef _SENDER_JIN_HPP
#define _SENDER_JIN_HPP

#include <iostream>
#include <fstream>
#include <random>
#include <Eigen/Dense>

#include "../file_stream/file_stream.hpp"


class sender_jin {
private:
    int m_nbits;
    int m_nsamplespersymbol;
    int m_nbitspersymbol;
    int m_eb;
    double m_no;
    int m_nbit2Decimal;
    Eigen::MatrixXi m_data;
    Eigen::MatrixXd m_signal;
    Eigen::MatrixXd m_ct;

public:
    sender_jin(int mNbits, int mNsamplespersymbol, int mNbitspersymbol, int mEb, double mNo);

    void transmitData();

    int binary2Decimal(Eigen::MatrixXi data);
};


#endif //_SENDER_JIN_HPP
