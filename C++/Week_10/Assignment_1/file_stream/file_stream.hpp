//
// Created by ParkJungJin on 2019-11-07.
//

#ifndef _FILE_STREAM_HPP
#define _FILE_STREAM_HPP

#include <fstream>
#include <iostream>

namespace Eigen {
    template<class Matrix>
    inline void write_binary(const std::string &filename, const Matrix &matrix) {
        std::ofstream out(filename, std::ios::out | std::ios::binary | std::ios::trunc);
        if (out.is_open()) {
            typename Matrix::Index rows = matrix.rows(), cols = matrix.cols();
            out.write(reinterpret_cast<char *>(&rows), sizeof(typename Matrix::Index));
            out.write(reinterpret_cast<char *>(&cols), sizeof(typename Matrix::Index));
            out.write(reinterpret_cast<const char *>(matrix.data()),
                      rows * cols * static_cast<typename Matrix::Index>(sizeof(typename Matrix::Scalar)));
            out.close();
        } else {
            std::cout << "Can not write to file: " << filename << std::endl;
        }
    }

    template<class Matrix>
    inline void read_binary(const std::string &filename, Matrix &matrix) {
        std::ifstream in(filename, std::ios::in | std::ios::binary);
        if (in.is_open()) {
            typename Matrix::Index rows = 0, cols = 0;
            in.read(reinterpret_cast<char *>(&rows), sizeof(typename Matrix::Index));
            in.read(reinterpret_cast<char *>(&cols), sizeof(typename Matrix::Index));
            matrix.resize(rows, cols);
            in.read(reinterpret_cast<char *>(matrix.data()),
                    rows * cols * static_cast<typename Matrix::Index>(sizeof(typename Matrix::Scalar)));
            in.close();
        } else {
            std::cout << "Can not open binary matrix file: " << filename << std::endl;
        }
    }
}
#endif //_FILE_STREAM_HPP
