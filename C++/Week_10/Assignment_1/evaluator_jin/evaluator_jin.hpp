//
// Created by ParkJungJin on 2019-11-07.
//

#ifndef _EVALUATOR_JIN_HPP
#define _EVALUATOR_JIN_HPP

#include <cmath>
#include <Eigen/Dense>
#include "../file_stream/file_stream.hpp"

class evaluator_jin {
private:
    int m_nbits;
    int m_nsamplespersymbol;
    int m_nbitspersymbol;
    int m_eb;
    double m_no;
    int m_k;
    double m_BER; //bit per error
    Eigen::MatrixXi m_data; //from the sender
    Eigen::MatrixXi m_decoded_data;//from the receiver
public:
    evaluator_jin(int mNbits, int mNsamplespersymbol, int mNbitspersymbol, int mEb, double mNo, double mk);

    void evaluate();

    void receiveData();
};

#endif //_EVALUATOR_JIN_HPP
