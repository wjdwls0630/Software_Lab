//
// Created by ParkJungJin on 2019-11-07.
//

#include "receiver_jin.hpp"

receiver_jin::receiver_jin(int mNbits, int mNsamplespersymbol, int mNbitspersymbol, int mEb, double mNo) :
        m_nbits(mNbits), m_nsamplespersymbol(mNsamplespersymbol), m_nbitspersymbol(mNbitspersymbol), m_eb(mEb),
        m_no(mNo),
        m_nbit2Decimal(int(pow(2, this->m_nbitspersymbol))),
        m_corrupted_signal(this->m_nbits / this->m_nbitspersymbol, this->m_nsamplespersymbol),
        m_ct(this->m_nbit2Decimal, this->m_nsamplespersymbol),
        m_constellation(this->m_nbits / this->m_nbitspersymbol, this->m_nbit2Decimal),
        m_decoded_data(this->m_nbits / this->m_nbitspersymbol, this->m_nbitspersymbol) {
    double t;
    double T = 0.01;
    //period 10ms
    double dt = T / this->m_nsamplespersymbol;
    double A = sqrt(this->m_eb);

    if (this->m_nbitspersymbol == 2) { //QPSK
        //phase is criterion on phase shift key
        //amplitude is not important things
        for (int i = 0; i < this->m_nbit2Decimal; i++) {
            //init time
            t = 0.0;
            for (int j = 0; j < this->m_nsamplespersymbol; j++, t += dt) {
                this->m_ct(i, j) = A * sqrt(2) * cos((2. * M_PI * t / T) + M_PI_4 + M_PI_2 + i);
            }
        }
    } else if (this->m_nbitspersymbol == 3) { //8PSK
        //phase is criterion on phase shift key
        //amplitude is not important things
        for (int i = 0; i < this->m_nbit2Decimal; i++) {
            //init time
            t = 0.0;
            for (int j = 0; j < this->m_nsamplespersymbol; j++, t += dt) {
                this->m_ct(i, j) = A * sqrt(2) * cos((2. * M_PI * t / T) + M_PI_4 + M_PI_4 * i);
            }
        }
    } else if (this->m_nbitspersymbol == 4) { //16 QAM
        for (int i = 0; i < this->m_nbit2Decimal; i++) {
            //init time
            t = 0.0;
            if (i % 4 == 0) {
                for (int j = 0; j < this->m_nsamplespersymbol; j++, t += dt) {
                    this->m_ct(i, j) = A * 0.25 * sqrt(2) * cos((2. * M_PI * t / T) + M_PI_4 + (i / 4) * M_PI_2);
                }
            } else if (i % 4 == 1) {
                for (int j = 0; j < this->m_nsamplespersymbol; j++, t += dt) {
                    this->m_ct(i, j) = A * sqrt(pow(0.25, 2) + pow(0.75, 2)) *
                                       cos((2. * M_PI * t / T) + atan(0.25 / 0.75) + (i / 4) * M_PI_2);
                }
            } else if (i % 4 == 2) {
                for (int j = 0; j < this->m_nsamplespersymbol; j++, t += dt) {
                    this->m_ct(i, j) = A * sqrt(pow(0.25, 2) + pow(0.75, 2)) *
                                       cos((2. * M_PI * t / T) + atan(0.75 / 0.25) + (i / 4) * M_PI_2);
                }
            } else if (i % 4 == 3) {
                for (int j = 0; j < this->m_nsamplespersymbol; j++, t += dt) {
                    this->m_ct(i, j) = A * 0.75 * sqrt(2) * cos((2. * M_PI * t / T) + M_PI_4 + (i / 4) * M_PI_2);
                }
            }
        }
    }
}

void receiver_jin::demodulate() {
    //for normalize
    //caution
    //need to use constant value when eigen matrix is declared, in this assignment we don't change # of samples
    Eigen::Matrix<double, 1, 20> temp;

    for (int i = 0; i < this->m_nbits / this->m_nbitspersymbol; i++) {
        temp = this->m_corrupted_signal.row(i);
        for (int j = 0; j < this->m_constellation.cols(); j++) {
            this->m_constellation(i, j) = temp.transpose().dot(this->m_ct.row(j));
        }

        int symbol = 0;

        if (this->m_nbitspersymbol <= 3) {
            //QPSK, 8PSK
            this->m_constellation.row(i).maxCoeff(&symbol);
            this->m_decoded_data.row(i) = this->decimal2Binary(symbol);
        }


    }

    Eigen::write_binary(
            "../data/Nbsym_" + std::to_string(this->m_nbitspersymbol) + "/decoded_data_N0_" +
            std::to_string(this->m_no) + ".dat",
            this->m_decoded_data);

    std::ofstream out_python(
            "../data/Nbsym_" + std::to_string(this->m_nbitspersymbol) + "/decoded_data_N0_" +
            std::to_string(this->m_no) + ".txt",
            std::ios::out);
    out_python << this->m_decoded_data << "\n";
    out_python.close();
}

void receiver_jin::receiveData() {
    Eigen::read_binary(
            "../data/Nbsym_" + std::to_string(this->m_nbitspersymbol) + "/channel_signal_N0_" +
            std::to_string(this->m_no) + ".dat",
            this->m_corrupted_signal);
}

Eigen::MatrixXi receiver_jin::decimal2Binary(int n) {
    Eigen::MatrixXi temp(1, this->m_nbitspersymbol);
    for (int i = 0; i < this->m_nbitspersymbol; i++) {
        temp(0, this->m_nbitspersymbol - 1 - i) = n % 2;
        n /= 2;
    }
    return temp;
}


