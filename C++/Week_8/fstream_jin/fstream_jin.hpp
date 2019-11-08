//
// Created by ParkJungJin on 2019-10-02.
//

#ifndef _FSTREAM_JIN_HPP
#define _FSTREAM_JIN_HPP

#include <fstream>
#include "../matrix_jin/matrix_jin.hpp"
#include "Error/file_not_found.hpp"

enum FileType {
    NORAML, MATRIX, WAV
};

class fstream_jin : public std::fstream {

private:
    std::string m_fname;
    std::string m_mode;
    FileType m_type;

public:
    fstream_jin(const std::string &t_Fname = "", const std::string &t_Type = "none", const std::string &t_Mode = "none")
            : m_mode(t_Mode) {
        if (t_Fname != "") {
            if (t_Type == "none") {
                this->m_type = FileType::NORAML;
            } else if (t_Type == "matrix") {
                this->m_type = FileType::MATRIX;
            } else if (t_Type == "wav") {
                this->m_type = FileType::WAV;
            }
        } else {
            this->m_fname = t_Fname;
            this->m_type = FileType::NORAML;
        }

    }

    virtual ~fstream_jin() {}

    const std::string &getFname() const { return this->m_fname; }

    void setFname(const std::string &t_Fname) { this->m_fname = t_Fname; }

    const FileType &getType() const { return this->m_type; }

    void setType(const std::string &t_Type) {
        if (t_Type == "none") {
            this->m_type = FileType::NORAML;
        } else if (t_Type == "matrix") {
            this->m_type = FileType::MATRIX;
        } else if (t_Type == "wav") {
            this->m_type = FileType::WAV;
        }
    }

    const std::string &getMode() const { return this->m_mode; }

    void setMode(const std::string &t_Mode) { this->m_mode = t_Mode; }

    virtual int
    open(const std::string &t_Fname = "", const std::string &t_Type = "none", const std::string &t_Mode = "none") {}

    virtual int close() {}
};


#endif //_FSTREAM_JIN_HPP
