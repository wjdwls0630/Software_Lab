//
// Created by ParkJungJin on 2019-10-02.
//

#ifndef _OFSTREAM_JIN_HPP
#define _OFSTREAM_JIN_HPP

#include "fstream_jin.hpp"
#include "Error/file_not_found.hpp"

template<typename T>
class ofstream_jin : public fstream_jin {
private:

    std::ofstream m_outFile;
public:
    ofstream_jin(const std::string &t_Fname = "", const std::string &t_Type = "none",
                 const std::string &t_Mode = "none")
            : fstream_jin(t_Fname, t_Type, t_Mode) {
        if (this->getFname() != "") {
            this->open(t_Fname, t_Type, t_Mode);
        }
    }

    virtual ~ofstream_jin() {
        if (this->m_outFile.is_open()) {
            this->m_outFile.close();
        }
    }

    //function
    int open(const std::string &t_Fname = "", const std::string &t_Type = "none", const std::string &t_Mode = "none");

    int write(const matrix_jin<T> &t_matrix);

    int write(const matrix_jin_3d &t_matrix);

    int close() {
        if (this->m_outFile.is_open()) {
            this->m_outFile.close();
            return 1;
        }
        return 0;
    }
};

template<typename T>
int ofstream_jin<T>::open(const std::string &t_Fname, const std::string &t_Type, const std::string &t_Mode) {
    //set file info
    this->setFname(t_Fname);
    this->setType(t_Type);
    this->setMode(t_Mode);

    if (this->getFname() != "") {
        if (this->getMode() == "none") {
            this->m_outFile.open(this->getFname());
            if (!this->m_outFile) {
                throw FileNotFound(t_Fname);
            }
        } else if (this->getMode() == "binary") {
            this->m_outFile.open(this->getFname(), std::ios::binary | std::ios::out);
            if (!this->m_outFile) {
                throw FileNotFound(t_Fname);
            }
        }
        return 1;
    }
    return 0;
}

template<typename T>
int ofstream_jin<T>::write(const matrix_jin<T> &t_matrix) {
    if (this->m_mode == "none") {
        for (int i = 0; i < t_matrix.getRow(); i++) {
            for (int j = 0; j < t_matrix.getCol(); j++) {
                this->m_outFile << t_matrix.getMatrix()[i * t_matrix.getCol() + j] << "\t";
            }
            this->m_outFile << "\n";
        }
        return 1;
    } else if (this->m_mode == "binary") {
        this->m_outFile.write((char *) t_matrix.getMatrix(), t_matrix.getLength() * sizeof(T));
        return 1;
    }
    return 0;
}

template<typename T>
int ofstream_jin<T>::write(const matrix_jin<T> &t_matrix) {
    if (this->m_mode == "none") {
        for (int i = 0; i < t_matrix.getRow(); i++) {
            for (int j = 0; j < t_matrix.getCol(); j++) {
                this->m_outFile << t_matrix.getMatrix()[i * t_matrix.getCol() + j] << "\t";
            }
            this->m_outFile << "\n";
        }
        return 1;
    } else if (this->m_mode == "binary") {
        this->m_outFile.write((char *) t_matrix.getMatrix(), t_matrix.getLength() * sizeof(T));
        return 1;
    }
    return 0;
}

template<typename T>
int ofstream_jin<T>::write(const matrix_jin_3d <T> &t_matrix) {
    if (this->m_mode == "none") {
        for (int i = 0; i < t_matrix.getRow(); i++) {
            for (int j = 0; j < t_matrix.getCol(); j++) {
                for (int k = 0; k < t_matrix.getHeight(); ++k) {
                    this->m_outFile << "[" << t_matrix.getMatrix()[i * t_matrix.getCol() + j * t_matrix.getHeight() + k]
                                    << ", ";
                }
                this->m_outFile << "]" << '\t';
            }
            this->m_outFile << "\n";
        }
        return 1;
    } else if (this->m_mode == "binary") {
        this->m_outFile.write((const char *) t_matrix.getMatrix(), t_matrix.getLength() * sizeof(T));
        return 1;
    }
    return 0;
}


#endif //_MATOFSTREAM_JIN_HPP
