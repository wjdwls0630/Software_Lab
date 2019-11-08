//
// Created by ParkJungJin on 2019-11-07.
//

#include "evaluator_jin.hpp"

evaluator_jin::evaluator_jin(int mNbits, int mNsamplespersymbol, int mNbitspersymbol, int mEb, double mNo, double mk) :
        m_nbits(mNbits), m_nsamplespersymbol(mNsamplespersymbol), m_nbitspersymbol(mNbitspersymbol), m_eb(mEb),
        m_no(mNo), m_k(mk), m_BER(0.0),
        m_data(this->m_nbits / this->m_nbitspersymbol, this->m_nbitspersymbol),
        m_decoded_data(this->m_nbits / this->m_nbitspersymbol, this->m_nbitspersymbol) {}

void evaluator_jin::evaluate() {

    //if just use resize, it disrupt the sequence of array,
    Eigen::RowVectorXi temp_data(1, this->m_nbits);
    Eigen::RowVectorXi temp_decoded_data(1, this->m_nbits);
    for (int i = 0; i < this->m_nbits / this->m_nbitspersymbol; i++) {
        for (int j = 0; j < this->m_nbitspersymbol; j++) {
            temp_data(0, i * this->m_nbitspersymbol + j) = this->m_data(i, j);
            temp_decoded_data(0, i * this->m_nbitspersymbol + j) = this->m_decoded_data(i, j);
        }
    }

    double errors = 0;
    for (int i = 0; i < this->m_nbits; i++) {
        if (temp_data(0, i) != temp_decoded_data(0, i)) {
            errors += 1;
        }
    }

    this->m_BER = errors / double(this->m_nbits);

    //write record
    std::ofstream out_python(
            "../data/BERvsK.txt", std::ios::app);
    out_python << this->m_k << " " << this->m_BER << '\n';
    std::cout << "Eb/No : " << this->m_k << "\t" << "BER : " << this->m_BER << '\n';
    out_python.close();
}

void evaluator_jin::receiveData() {
    //original data
    Eigen::read_binary(
            "../data/Nbsym_" + std::to_string(this->m_nbitspersymbol) + "/original_data_N0_" +
            std::to_string(this->m_no) + ".dat",
            this->m_data);

    //decoded data
    Eigen::read_binary(
            "../data/Nbsym_" + std::to_string(this->m_nbitspersymbol) + "/decoded_data_N0_" +
            std::to_string(this->m_no) + ".dat",
            this->m_decoded_data);
}

