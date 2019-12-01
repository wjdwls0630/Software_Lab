//
// Created by ParkJungJin on 2019-11-24.
//

#ifndef _FFT_JIN_HPP
#define _FFT_JIN_HPP


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

enum FFT_MODE {
    FORWARD, INVERSE
};

template<typename T>
class fft_jin {
private:
    matrix_jin<std::complex<T>> *x_n;
    matrix_jin<std::complex<T>> *X_k;
public:
    /**
    *	default constructor.
    */
    fft_jin(int n_or_k = FT_DATA::N, matrix_jin<std::complex<T>> *data = nullptr);

    /**
    *	destructor
    */
    virtual ~fft_jin();

    //operation
    void FFT(int mode = FFT_MODE::FORWARD);

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
fft_jin<T>::fft_jin(int n_or_k, matrix_jin<std::complex<T>> *data):x_n(nullptr), X_k(nullptr) {
    if (data != nullptr) {
        if (n_or_k == FT_DATA::N) {
            //data is n domain
            this->x_n = new matrix_jin<std::complex<T>>(data->getLength(), 1, "x[n]");
            this->X_k = new matrix_jin<std::complex<T>>(data->getLength(), 1, "X[k]");
            *this->x_n = *data; //deep copy
            //make X[k]
            this->FFT(FFT_MODE::FORWARD);
        } else {
            //data is k domain
            this->X_k = new matrix_jin<std::complex<T>>(data->getLength(), 1, "X[k]");
            this->x_n = new matrix_jin<std::complex<T>>(data->getLength(), 1, "x[n]");
            *this->X_k = *data; //deep copy

            //make X[k]
            this->FFT(FFT_MODE::INVERSE);
        }
    }

}

template<typename T>
fft_jin<T>::~fft_jin() {
    if (this->x_n != nullptr) {
        delete this->x_n;
    }
    if (this->X_k != nullptr) {
        delete this->X_k;
    }
}

template<typename T>
void fft_jin<T>::FFT(int mode) {

    //initialize nN
    int nN = 0;
    if (mode == FFT_MODE::FORWARD) {
        nN = this->x_n->getLength();
    } else {
        nN = this->X_k->getLength();
    }

    if (nN <= 1) {
        return;
    }

    std::complex<T> temp_comp1; // temp value 1
    std::complex<T> W(0, 0); //rotation argument

    //result Foward : X[k] Inverse : x[n]
    matrix_jin<std::complex<T>> *result = nullptr;
    result = new matrix_jin<std::complex<T>>(nN, 1);

    //deep copy
    if (mode == FFT_MODE::FORWARD) {
        *result = *this->x_n;
    } else {
        *result = *this->X_k;
    }

    int j = 0, k = 0;
    for (int i = 1; i < (nN - 1); i++) {   // (1) i = 1, j = 0, k = 0 (2) i =2, (3) i=3 (4) i =4,j=6 (5)i = 5, j =4
        k = nN / 2; //  // k = 4  (2) k=4 (3) k=4,j=2 (4) k = 4 (5) k=4
        while (k <= j) {// (1) k=4, j=0 (x) (2) j =4, k=4 (o) (3) x (4) (o) (5) (o)
            j = j - k;  // (2) j =0 (4) j = 2  (5) j = 0
            k = k / 2;  // (2)k =2  (4) k = 2 *5) k = 2
        }
        j = j + k; //(1) j = 4, (2) j = 2 (3) j=6, (4) j = 4,
        if (i < j) {  //(2) j =2 k=2     (3) i = 3, j=6   (4) j =4, i = 4
            // (1) i=1 j =4 swap, (3) 3, 6 swap
            // j = 4, i = 1 swap
            // j = 4, i = 1 swap
            // j = 4, i = 1 swap  (1,4)
            temp_comp1 = result->operator[](j);
            result->operator[](j) = result->operator[](i);
            result->operator[](i) = temp_comp1;
        }
    }

    double Tr, Ti;
    std::complex<T> temp_comp2; // temp value 2
    int iter, j2, pos;
    k = nN >> 1;  // (0) k= 1000<2>  k = 100<2> =4
    iter = 1;
    while (k > 0) {
        j = 0;
        j2 = 0;

        for (int i = 0; i < nN >> 1; i++) {  // 0 ~i ~4 (1) i =0, (2) i=1 j=2, k =4 (3) i=2, j =4 (4) j =6,
            if (mode == FFT_MODE::FORWARD) {
                W = std::polar<T>(1, -2.0 * M_PI * (j2 * k) / nN);
            } else {
                W = std::polar<T>(1, 2.0 * M_PI * (j2 * k) / nN);
            }
            pos = j + (1 << (iter - 1)); // (1) pos = 1 = 1 (2)pos 2+1=3 (3) pos =5 j =4 (4) j =6, pos=7
            temp_comp2.real(result->operator[](pos).real() * W.real() - result->operator[](pos).imag() * W.imag());
            temp_comp2.imag(result->operator[](pos).real() * W.imag() + result->operator[](pos).imag() * W.real());

            // (1) Y[pos=1], j = 0 (2) y[2] y[3]: X[2],X[6], (3)y[4],[5] (4) y[6],[7]
            result->operator[](pos) = result->operator[](j) - temp_comp2;

            result->operator[](j) += temp_comp2;

            j += 1 << iter; // j= 0+ 10<2>= 2 (2) j = 2+ 2 = 4 =100(3) j=1000=6 , j =12
            if (j >= nN) j = ++j2; //(1) x (2) (3) o j = 1, j2=1
        }
        k >>= 1; // (1) k = k>>1; 100=4 :: 10=2
        iter++; // (1) iter=2
    }
    if (mode == FFT_MODE::INVERSE) {
        for (int i = 0; i < nN; i++) {
            result->operator[](i) /= nN;
        }
    }

    if (mode == FFT_MODE::FORWARD) {
        *this->X_k = *result;
    } else {
        *this->x_n = *result;
    }
}

template<typename T>
int fft_jin<T>::writeFile_x_n_MagPh(const std::string &t_fname) {
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
int fft_jin<T>::writeFile_x_n_ReIm(const std::string &t_fname) {

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
int fft_jin<T>::writeFile_X_k_MagPh(const std::string &t_fname) {
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
int fft_jin<T>::writeFile_X_k_ReIm(const std::string &t_fname) {

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
int fft_jin<T>::readFile_x_n_MagPh(const std::string &t_fname, int mode) {
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
    this->FFT(FFT_MODE::FORWARD);

    //file close
    in_x_n.close();

    //deallocate memory

    delete temp_x_n;

    return 1;
}

template<typename T>
int fft_jin<T>::readFile_x_n_ReIm(const std::string &t_fname, int mode) {
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
    this->FFT(FFT_MODE::FORWARD);

    //file close
    in_x_n.close();

    //deallocate memory

    delete temp_x_n;

    return 1;
}

template<typename T>
int fft_jin<T>::readFile_X_k_MagPh(const std::string &t_fname, int mode) {

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
    this->FFT(FFT_MODE::INVERSE);

    //file close
    in_X_k.close();

    //deallocate memory

    delete temp_X_k;

    return 1;
}

template<typename T>
int fft_jin<T>::readFile_X_k_ReIm(const std::string &t_fname, int mode) {
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
    this->FFT(FFT_MODE::INVERSE);

    //file close
    in_X_k.close();

    //deallocate memory

    delete temp_X_k;

    return 1;
}


#endif //_FFT_JIN_HPP
