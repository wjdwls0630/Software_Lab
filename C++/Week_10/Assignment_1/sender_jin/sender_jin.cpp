//
// Created by ParkJungJin on 2019-11-07.
//

#include "sender_jin.hpp"


sender_jin::sender_jin(int mNbits, int mNsamplespersymbol, int mNbitspersymbol, int mEb, double mNo)
        : m_nbits(mNbits), m_nsamplespersymbol(mNsamplespersymbol), m_nbitspersymbol(mNbitspersymbol), m_eb(mEb),
          m_no(mNo), m_nbit2Decimal(int(pow(2, this->m_nbitspersymbol))),
          m_data(this->m_nbits / this->m_nbitspersymbol, this->m_nbitspersymbol),
          m_signal(this->m_nbits / this->m_nbitspersymbol, this->m_nsamplespersymbol),
          m_ct(this->m_nbit2Decimal, this->m_nsamplespersymbol) {

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

void sender_jin::transmitData() {



    //for random
    std::random_device rd;
    std::mt19937_64 rng(rd());
    std::uniform_int_distribution<int> dist(0, 1);

    //initiallize data
    for (int i = 0; i < this->m_nbits / this->m_nbitspersymbol; i++) {
        for (int j = 0; j < this->m_nbitspersymbol; j++) {
            this->m_data(i, j) = dist(rng);
        }
    }

    //to contain bits
    Eigen::MatrixXi temp(1, this->m_nbitspersymbol);

    //generate symbol
    for (int i = 0; i < this->m_nbits / this->m_nbitspersymbol; i++) {
        temp = this->m_data.row(i);
        this->m_signal.row(i) = this->m_ct.row(this->binary2Decimal(temp));
    }

    Eigen::write_binary(
            "../data/NbSym_" + std::to_string(this->m_nbitspersymbol) + "/original_signal_N0_" +
            std::to_string(this->m_no) + ".dat",
            this->m_signal);

    Eigen::write_binary("../data/Nbsym_" + std::to_string(this->m_nbitspersymbol) + "/original_data_N0_" +
                        std::to_string(this->m_no) + ".dat",
                        this->m_data);

    std::ofstream out_python(
            "../data/Nbsym_" + std::to_string(this->m_nbitspersymbol) + "/original_data__N0_" +
            std::to_string(this->m_no) + ".txt",
            std::ios::out);

    out_python << this->m_data << '\n';
    out_python.close();
}

int sender_jin::binary2Decimal(Eigen::MatrixXi data) {
    int sum = 0;
    for (int i = 0; i < this->m_nbitspersymbol; i++) {
        sum += data(0, i) * int(pow(2, this->m_nbitspersymbol - 1 - i));
    }
    return sum;
}

