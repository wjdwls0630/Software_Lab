#pragma once

#include <eigen/Dense>
#include <eigen/LU>

using namespace Eigen;

class basis {
public:
    basis() {};

    basis(int n, int type);

    VectorXd c;
};
