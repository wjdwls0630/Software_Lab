//
// Created by ParkJungJin on 2019-09-30.
//

#include <iostream>
#include <fstream>

#include "../matrix_jin/matrix_jin.hpp"
#include "../matfstream_jin/matofstream_jin.hpp"
#include "../matfstream_jin/matifstream_jin.hpp"


int main() {
    std::ifstream infile;
    infile.open("aaa1.m4a", std::ios::binary | std::ios::in);
    infile.seekg(0, std::ios::end);
    int fileSize = infile.tellg();
    infile.close();
    infile.open("aaa1.m4a", std::ios::binary | std::ios::in);

    std::ofstream outfile;
    outfile.open("aaa2.m4a", std::ios::binary | std::ios::out);
    int buffer[6];
    int n = 0;
    while (infile.read((char *) &buffer, sizeof(buffer))) {
        outfile.write((char *) &buffer, sizeof(buffer));
        n += sizeof(buffer);
    }
    std::cout << n << " out of " << fileSize << '\n';
    infile.close();
    outfile.close();

    return 1;
}

