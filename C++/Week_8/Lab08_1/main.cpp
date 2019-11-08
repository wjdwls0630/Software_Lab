//
// Created by ParkJungJin on 2019-09-30.
//

#include <fstream>
#include <cstdlib>
#include <ctime>
#include "../matrix_jin/matrix_jin.hpp"
#include "../matfstream_jin/matofstream_jin.hpp"
#include "../matfstream_jin/matifstream_jin.hpp"


int main() {
    try {
        Matrix_Jin<double> A(3, 2);
        for (int i = 0; i < A.getLength(); ++i) {
            A[i] = i + 1;
        }
        A.setName("A");
        A.showMatrix();

        A.setName("A^T");
        A.transpose();
        A.showMatrix();

        double *t_list;
        t_list = new double[3]{1., 2., 3.};

        A.setName("A^T_appendRow");
        A.appendRow(t_list, 3, 1);
        A.showMatrix();

        A.setName("A^T_appendCol");
        A.appendCol(t_list, 3, 1);
        A.showMatrix();


        double *temp;
        temp = new double[8]{0, 1, 3, 2, 5, 2, 3, 4};
        Matrix_Jin<double> B(4, 2, temp);
        delete[] temp;

        B.setName("B");
        B.showMatrix();

        A *= B;
        std::cout << "A = A*B" << '\n';
        A.showMatrix();

        std::cout << "orthonormalized" << '\n';

        double *c0, *c1, *c2, *c3;
        c0 = new double[4]{1, 1, 1, 1};
        c1 = new double[4]{1, 1, -1, -1};
        c2 = new double[4]{1, -1, -1, 1};
        c3 = new double[4]{1, -1, 1, -1};
        Matrix_Jin<double> C(1, 4, c0, "C");
        C.appendRow(c1, 4, 1);
        C.appendRow(c2, 4, 1);
        C.appendRow(c3, 4, 1);

        C.showMatrix();
        C.setName("C_Normalized");
        C.normalize();
        C.showMatrix();

        Matrix_Jin<double> C_T(C);
        C_T.transpose();
        C_T.setName("C^T");
        C_T.showMatrix();

        Matrix_Jin<double> result = C * C_T;
        result.setName("CC^T");
        result.showMatrix();

        A.makeEmpty();
        Matrix_Jin<double> a(4, 1);
        srand(time(NULL));
        for (int j = 0; j < a.getLength(); ++j) {
            a[j] = rand() % 99 + 1;
        }

        a.setName("a");
        a.showMatrix();

        A = C * a;
        A.setName("A");
        A.showMatrix();
        result = C_T * A;
        result.setName("C^T A = a");
        result.showMatrix();

        MatOfstream_Jin<double> myout("mt.dat");
        myout.write(A);
        myout.close();

        myout.open("mt_binary.dat", "binary");

        myout.write(B);
        myout.close();

        MatIfstream_Jin<double> myin("mt_binary.dat", "binary");
        A.makeEmpty();
        A.setName("A");
        A.setRow(4);
        A.setCol(2);
        A.setLength(8);
        myin.read(A);
        A.showMatrix();


    } catch (std::exception &e) {
        std::cout << e.what() << '\n';
    }


    return 1;
}

