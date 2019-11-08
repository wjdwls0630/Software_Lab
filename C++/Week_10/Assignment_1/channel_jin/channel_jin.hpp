//
// Created by ParkJungJin on 2019-11-07.
//

#ifndef _CHANNEL_JIN_HPP
#define _CHANNEL_JIN_HPP

#include <iostream>
#include <fstream>
#include <random>
#include <Eigen/Dense>
#include "../file_stream/file_stream.hpp"

class channel_jin {

private:
    int m_nbits;
    int m_nsamplespersymbol;
    int m_nbitspersymbol;
    int m_eb;
    double m_no;
    Eigen::MatrixXd m_signal; // original signal
    Eigen::MatrixXd m_corrupted_signal; //corrupted signal with gaussian noise

public:
    channel_jin(int mNbits, int mNsamplespersymbol, int mNbitspersymbol, int mEb, double mNo);

    void AWGN();

    void receiveData();

    void transmitData();
};


#endif //_CHANNEL_JIN_HPP
