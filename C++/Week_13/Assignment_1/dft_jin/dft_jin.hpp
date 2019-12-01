//
// Created by ParkJungJin on 2019-11-24.
//

#ifndef _DFT_JIN_HPP
#define _DFT_JIN_HPP

#include <fstream>
#include <cmath>
#include <complex>
#include <string>
#include "../matrix_jin/matrix_jin.hpp"
#include "../matfstream_jin/matifstream_jin.hpp"
#include "../matfstream_jin/matofstream_jin.hpp"

/**
 * Caution:: it is only work on 1D array (col = 1)
 *
 *
 */
enum FT_DATA {
    N, K
};


template<typename T>
class dft_jin {
private:
    matrix_jin<std::complex<T>> *x_n;
    matrix_jin<std::complex<T>> *X_k;
public:
    /**
    *	default constructor.
    */
    dft_jin(int n_or_k = FT_DATA::N, matrix_jin<std::complex<T>> *data = nullptr);

    /**
    *	destructor
    */
    virtual ~dft_jin();

    //operation
    void DFT();

    void IDFT();

    int writeFile_x_n_MagPh(const std::string &t_fname);

    int writeFile_x_n_ReIm(const std::string &t_fname);

    int writeFile_X_k_MagPh(const std::string &t_fname);

    int writeFile_X_k_ReIm(const std::string &t_fname);

    /**
    *	@brief	read x[n] data(Mag, Phase) from file
    *	@pre	none.
    *	@post	set x[n], X[k].
    *	@details mode == 1 -> Mag '\t' Ph mode == 2 -> Mag
    *	@return if all process is done, return 1
    */
    int readFile_x_n_MagPh(const std::string &t_fname, int mode = 1);

    /**
    *	@brief	read x[n] data(Real, Imag) from file
    *	@pre	none.
    *	@post	set x[n], X[k].
    *	@details mode == 1 -> Re '\t' Im mode == 2 -> Re
    *	@return if all process is done, return 1
    */
    int readFile_x_n_ReIm(const std::string &t_fname, int mode = 1);

    /**
    *	@brief	read X[k] data(Mag, Phase) from file
    *	@pre	none.
    *	@post	set x[n], X[k].
    *	@details mode == 1 -> Mag '\t' Ph mode == 2 -> Mag
    *	@return if all process is done, return 1
    */
    int readFile_X_k_MagPh(const std::string &t_fname, int mode = 1);

    /**
    *	@brief	read X[k] data(Real, Imag) from file
    *	@pre	none.
    *	@post	set x[n], X[k].
    *	@details mode == 1 -> Re '\t' Im mode == 2 -> Re
    *	@return if all process is done, return 1
    */
    int readFile_X_k_ReIm(const std::string &t_fname, int mode = 1);

};

template<typename T>
dft_jin<T>::dft_jin(int n_or_k, matrix_jin<std::complex<T>> *data):x_n(nullptr), X_k(nullptr) {
    if (data != nullptr) {
        if (n_or_k == FT_DATA::N) {
            //data is n domain
            this->x_n = new matrix_jin<std::complex<T>>(data->getLength(), 1, "x[n]");
            this->X_k = new matrix_jin<std::complex<T>>(data->getLength(), 1, "X[k]");
            *this->x_n = *data; //deep copy

            //make X[k]
            this->DFT();
        } else {
            //data is k domain
            this->X_k = new matrix_jin<std::complex<T>>(data->getLength(), 1, "X[k]");
            this->x_n = new matrix_jin<std::complex<T>>(data->getLength(), 1, "x[n]");
            *this->X_k = *data; //deep copy

            //make x[n]
            this->IDFT();
        }
    }
}

template<typename T>
dft_jin<T>::~dft_jin() {
    if (this->x_n != nullptr) {
        delete this->x_n;
    }
    if (this->X_k != nullptr) {
        delete this->X_k;
    }
}

template<typename T>
void dft_jin<T>::DFT() {
    for (int k = 0; k < this->x_n->getLength(); k++) {
        //initialize
        this->X_k->operator[](k) = 0;
        for (int n = 0; n < this->x_n->getLength(); n++) {
            this->X_k->operator[](k) += this->x_n->operator[](n) *
                                        std::polar<T>(1, (-2.0 * M_PI * k * n) / (double) this->x_n->getLength());
        }
    }
}

template<typename T>
void dft_jin<T>::IDFT() {
    for (int n = 0; n < this->X_k->getLength(); n++) {
        //initialize
        this->x_n->operator[](n) = 0;
        for (int k = 0; k < this->X_k->getLength(); k++) {
            this->x_n->operator[](n) +=
                    this->X_k->operator[](k) * std::polar<T>(1, (2.0 * M_PI * k * n) / (double) this->X_k->getLength());
        }
        this->x_n->operator[](n) /= (double) this->X_k->getLength();
    }
}

template<typename T>
int dft_jin<T>::writeFile_x_n_MagPh(const std::string &t_fname) {
    //file record
    matofstream_jin<T> out_x_n(t_fname);

    //temp
    matrix_jin<T> *temp_x_n = nullptr;
    temp_x_n = new matrix_jin<T>(this->x_n->getLength(), 2);

    //mag \t phase
    for (int i = 0; i < this->x_n->getLength(); i++) {
        temp_x_n->operator[](i * temp_x_n->getCol()) = std::abs(this->x_n->operator[](i));
        temp_x_n->operator[](i * temp_x_n->getCol() + 1) = std::arg(this->x_n->operator[](i));
    }

    //file write
    out_x_n.write(*temp_x_n);

    //file close
    out_x_n.close();


    //deallocate memory

    delete temp_x_n;

    return 1;
}

template<typename T>
int dft_jin<T>::writeFile_x_n_ReIm(const std::string &t_fname) {

    //file record
    matofstream_jin<T> out_x_n(t_fname);

    //temp
    matrix_jin<T> *temp_x_n = nullptr;
    temp_x_n = new matrix_jin<T>(this->x_n->getLength(), 2);

    //Real \t Imag
    for (int i = 0; i < this->x_n->getLength(); i++) {
        temp_x_n->operator[](i * temp_x_n->getCol()) = this->x_n->operator[](i).real();
        temp_x_n->operator[](i * temp_x_n->getCol() + 1) = this->x_n->operator[](i).imag();
    }

    //file write
    out_x_n.write(*temp_x_n);

    //file close
    out_x_n.close();

    //deallocate memory

    delete temp_x_n;

    return 1;
}

template<typename T>
int dft_jin<T>::writeFile_X_k_MagPh(const std::string &t_fname) {
    //file record
    matofstream_jin<T> out_X_k(t_fname);

    //temp
    matrix_jin<T> *temp_X_k = nullptr;
    temp_X_k = new matrix_jin<T>(this->X_k->getLength(), 2);

    //mag \t phase
    for (int i = 0; i < this->X_k->getLength(); i++) {
        temp_X_k->operator[](i * temp_X_k->getCol()) = std::abs(this->X_k->operator[](i));
        temp_X_k->operator[](i * temp_X_k->getCol() + 1) = std::arg(this->X_k->operator[](i));
    }

    //file write
    out_X_k.write(*temp_X_k);

    //file close
    out_X_k.close();


    //deallocate memory

    delete temp_X_k;

    return 1;
}

template<typename T>
int dft_jin<T>::writeFile_X_k_ReIm(const std::string &t_fname) {

    //file record
    matofstream_jin<T> out_X_k(t_fname);

    //temp
    matrix_jin<T> *temp_X_k = nullptr;
    temp_X_k = new matrix_jin<T>(this->X_k->getLength(), 2);

    //Real \t Imag
    for (int i = 0; i < this->X_k->getLength(); i++) {
        temp_X_k->operator[](i * temp_X_k->getCol()) = this->X_k->operator[](i).real();
        temp_X_k->operator[](i * temp_X_k->getCol() + 1) = this->X_k->operator[](i).imag();
    }

    //file write
    out_X_k.write(*temp_X_k);

    //file close
    out_X_k.close();

    //deallocate memory

    delete temp_X_k;

    return 1;
}

template<typename T>
int dft_jin<T>::readFile_x_n_MagPh(const std::string &t_fname, int mode) {
    //get # of data
    std::ifstream temp_in(t_fname);
    int temp_N = 0;
    char temp_line[255];

    while (!temp_in.eof()) {
        temp_in.getline(temp_line, 255);
        temp_N++;
    }

    //reduce eof sign
    temp_N--;

    //temp file close
    temp_in.close();

    //file record
    matifstream_jin<T> in_x_n(t_fname);

    matrix_jin<T> *temp_x_n = nullptr;

    if (mode == 1) {
        temp_x_n = new matrix_jin<T>(temp_N, 2);
    } else if (mode == 2) {
        temp_x_n = new matrix_jin<T>(temp_N, 1);
    }


    //mag \t phase

    //file read
    in_x_n.read(*temp_x_n);

    //create container
    if (this->x_n != nullptr) {
        delete this->x_n;
    }

    if (this->X_k != nullptr) {
        delete this->X_k;
    }

    this->x_n = new matrix_jin<std::complex<T>>(temp_N, 1, "x[n]");
    this->X_k = new matrix_jin<std::complex<T>>(temp_N, 1, "X[k]");

    //initialize x[n]
    if (mode == 1) {
        for (int i = 0; i < temp_x_n->getLength() / 2; i++) {
            this->x_n->operator[](i) = std::polar<T>(
                    temp_x_n->operator[](i * temp_x_n->getCol()), temp_x_n->operator[](i * temp_x_n->getCol() + 1));
        }
    } else if (mode == 2) {
        for (int i = 0; i < temp_x_n->getLength(); i++) {
            this->x_n->operator[](i) = std::complex<T>(temp_x_n->operator[](i), 0);
        }
    }

    //create X[k]
    this->DFT();

    //file close
    in_x_n.close();

    //deallocate memory

    delete temp_x_n;

    return 1;
}

template<typename T>
int dft_jin<T>::readFile_x_n_ReIm(const std::string &t_fname, int mode) {
    //get # of data
    std::ifstream temp_in(t_fname);
    int temp_N = 0;
    char temp_line[255];

    while (!temp_in.eof()) {
        temp_in.getline(temp_line, 255);
        temp_N++;
    }

    //reduce eof sign
    temp_N--;

    //temp file close
    temp_in.close();

    //file record
    matifstream_jin<T> in_x_n(t_fname);

    matrix_jin<T> *temp_x_n = nullptr;
    if (mode == 1) {
        temp_x_n = new matrix_jin<T>(temp_N, 2);
    } else if (mode == 2) {
        temp_x_n = new matrix_jin<T>(temp_N, 1);
    }

    //re \t im

    //file read
    in_x_n.read(*temp_x_n);

    //create container
    if (this->x_n != nullptr) {
        delete this->x_n;
    }

    if (this->X_k != nullptr) {
        delete this->X_k;
    }

    this->x_n = new matrix_jin<std::complex<T>>(temp_N, 1, "x[n]");
    this->X_k = new matrix_jin<std::complex<T>>(temp_N, 1, "X[k]");

    //initialize x[n]
    if (mode == 1) {
        for (int i = 0; i < temp_x_n->getLength() / 2; i++) {
            this->x_n->operator[](i) = std::complex<T>(
                    temp_x_n->operator[](i * temp_x_n->getCol()), temp_x_n->operator[](i * temp_x_n->getCol() + 1));
        }
    } else if (mode == 2) {
        for (int i = 0; i < temp_x_n->getLength(); i++) {
            this->x_n->operator[](i) = std::complex<T>(temp_x_n->operator[](i), 0);
        }
    }



    //create X[k]
    this->DFT();

    //file close
    in_x_n.close();

    //deallocate memory

    delete temp_x_n;

    return 1;
}

template<typename T>
int dft_jin<T>::readFile_X_k_MagPh(const std::string &t_fname, int mode) {

    //get # of data
    std::ifstream temp_in(t_fname);
    int temp_N = 0;
    char temp_line[255];

    while (!temp_in.eof()) {
        temp_in.getline(temp_line, 255);
        temp_N++;
    }
    //reduce eof sign
    temp_N--;

    //temp file close
    temp_in.close();

    //file record
    matifstream_jin<T> in_X_k(t_fname);

    matrix_jin<T> *temp_X_k = nullptr;
    if (mode == 1) {
        temp_X_k = new matrix_jin<T>(temp_N, 2);
    } else if (mode == 2) {
        temp_X_k = new matrix_jin<T>(temp_N, 1);
    }

    //re \t im

    //file read
    in_X_k.read(*temp_X_k);

    //create container
    if (this->x_n != nullptr) {
        delete this->x_n;
    }

    if (this->X_k != nullptr) {
        delete this->X_k;
    }

    this->x_n = new matrix_jin<std::complex<T>>(temp_N, 1, "x[n]");
    this->X_k = new matrix_jin<std::complex<T>>(temp_N, 1, "X[k]");

    //initialize X[k]

    if (mode == 1) {
        for (int i = 0; i < temp_X_k->getLength() / 2; i++) {
            this->X_k->operator[](i) = std::polar<T>(
                    temp_X_k->operator[](i * temp_X_k->getCol()), temp_X_k->operator[](i * temp_X_k->getCol() + 1));
        }
    } else if (mode == 2) {
        for (int i = 0; i < temp_X_k->getLength(); i++) {
            this->X_k->operator[](i) = std::complex<T>(temp_X_k->operator[](i), 0);
        }
    }

    //create x[n]
    this->IDFT();

    //file close
    in_X_k.close();

    //deallocate memory

    delete temp_X_k;

    return 1;
}

template<typename T>
int dft_jin<T>::readFile_X_k_ReIm(const std::string &t_fname, int mode) {
    //get # of data
    std::ifstream temp_in(t_fname);
    int temp_N = 0;
    char temp_line[255];

    while (!temp_in.eof()) {
        temp_in.getline(temp_line, 255);
        temp_N++;
    }

    //reduce eof sign
    temp_N--;

    //temp file close
    temp_in.close();

    //file record
    matifstream_jin<T> in_X_k(t_fname);

    matrix_jin<T> *temp_X_k = nullptr;
    if (mode == 1) {
        temp_X_k = new matrix_jin<T>(temp_N, 2);
    } else if (mode == 2) {
        temp_X_k = new matrix_jin<T>(temp_N, 1);
    }


    //re \t im

    //file read
    in_X_k.read(*temp_X_k);

    //create container
    if (this->x_n != nullptr) {
        delete this->x_n;
    }

    if (this->X_k != nullptr) {
        delete this->X_k;
    }

    this->x_n = new matrix_jin<std::complex<T>>(temp_N, 1, "x[n]");
    this->X_k = new matrix_jin<std::complex<T>>(temp_N, 1, "X[k]");

    //initialize X[k]

    if (mode == 1) {
        for (int i = 0; i < temp_X_k->getLength() / 2; i++) {
            this->X_k->operator[](i) = std::complex<T>(
                    temp_X_k->operator[](i * temp_X_k->getCol()), temp_X_k->operator[](i * temp_X_k->getCol() + 1));
        }
    } else if (mode == 2) {
        for (int i = 0; i < temp_X_k->getLength(); i++) {
            this->X_k->operator[](i) = std::complex<T>(temp_X_k->operator[](i), 0);
        }
    }


    //create x[n]
    this->IDFT();

    //file close
    in_X_k.close();

    //deallocate memory

    delete temp_X_k;

    return 1;
}


#endif //_DFT_JIN_HPP
