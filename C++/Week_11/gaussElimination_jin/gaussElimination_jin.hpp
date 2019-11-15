//
// Created by ParkJungJin on 2019-11-13.
//

#ifndef GAUSSELIMINATION_JIN_HPP
#define GAUSSELIMINATION_JIN_HPP

#include <iostream>
#include <Eigen/Dense>

//has solution return 1, no solution return 0
int gaussElimination_jin(Eigen::MatrixXd &A, Eigen::VectorXd &B);

#endif //GAUSSELIMINATION_JIN_HPP
