//
// Created by ParkJungJin on 2019-11-07.
//

#include "channel_jin.hpp"

channel_jin::channel_jin(int mNbits, int mNsamplespersymbol, int mNbitspersymbol, int mEb, double mNo) :
        m_nbits(mNbits), m_nsamplespersymbol(mNsamplespersymbol), m_nbitspersymbol(mNbitspersymbol), m_eb(mEb),
        m_no(mNo),
        m_signal(this->m_nbits / this->m_nbitspersymbol, this->m_nsamplespersymbol),
        m_corrupted_signal(this->m_nbits / this->m_nbitspersymbol, this->m_nsamplespersymbol) {}

void channel_jin::AWGN() {
    //for random
    std::random_device rd;
    std::mt19937_64 rng(rd());
    std::normal_distribution<double> dist(0, this->m_no);

    for (int i = 0; i < this->m_nbits / this->m_nbitspersymbol; i++) {
        for (int j = 0; j < this->m_nsamplespersymbol; j++) {
            this->m_corrupted_signal(i, j) = this->m_signal(i, j) + dist(rng);
        }

    }
}

void channel_jin::receiveData() {
    Eigen::read_binary(
            "../data/Nbsym_" + std::to_string(this->m_nbitspersymbol) + "/original_signal_N0_" +
            std::to_string(this->m_no) + ".dat",
            this->m_signal);
}

void channel_jin::transmitData() {
    Eigen::write_binary(
            "../data/Nbsym_" + std::to_string(this->m_nbitspersymbol) + "/channel_signal_N0_" +
            std::to_string(this->m_no) + ".dat",
            this->m_corrupted_signal);
}


