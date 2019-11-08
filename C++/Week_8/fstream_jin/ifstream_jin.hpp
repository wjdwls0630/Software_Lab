//
// Created by ParkJungJin on 2019-10-02.
//

#ifndef _ifstream_jin_HPP
#define _ifstream_jin_HPP

#include "fstream_jin.hpp"

class ifstream_jin : public fstream_jin {
private:
    std::ifstream m_inFile;
public:
    ifstream_jin(const std::string &t_Fname = "", const std::string &t_Mode = "none",
                 const std::stirng &t_Type = "none")
            : fstream_jin(t_Fname, t_Mode, t_Type) {
        if (this->getFname() != "") {
            if (this->getMode() == "binary") {
                this->open(this->getFname(), std::ios::binary);
            } else {
                this->open(this->getFname());
            }
        }
    }

    virtual ~ifstream_jin() {
        if (this->m_inFile.is_open()) {
            this->m_inFile.close();
        }
    }


    //function
    int open(const std::string &t_Filename = "", const std::string &t_mode = "none");

    int read(const matrix_jin<T> &t_matrix);

    int close() {
        if (this->m_inFile.is_open()) {
            this->m_inFile.close();
            return 1;
        }
        return 0;
    }
};

template<typename T>
int ifstream_jin<T>::open(const std::string &t_Filename, const std::string &t_mode) {
    if (this->getFname() != "") {
        if (this->m_mode == "none") {
            this->m_inFile.open(this->m_fname);
            if (!this->m_inFile) {
                throw FileNotFound(t_Filename);
            }
        } else if (this->m_mode == "binary") {
            this->m_inFile.open(this->m_fname, std::ios::binary | std::ios::out);
            if (!this->m_inFile) {
                throw FileNotFound(t_Filename);
            }
        }
        return 1;
    }
    return 0;
}

template<typename T>
int ifstream_jin<T>::read(const matrix_jin<T> &t_matrix) {
    if (this->m_mode == "none") {
        for (int i = 0; i < t_matrix.getLength(); i++) {
            this->m_inFile >> t_matrix.getMatrix()[i];
        }
        return 1;
    } else if (this->m_mode == "binary") {
        this->m_inFile.read((char *) t_matrix.getMatrix(), t_matrix.getLength() * sizeof(T));
        return 1;
    }
    return 0;
}


#endif //_ifstream_jin_HPP
