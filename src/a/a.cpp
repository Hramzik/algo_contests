
//--------------------------------------------------

#include <iostream>
#include <cassert>

//--------------------------------------------------

#include "a.hpp"

//--------------------------------------------------


int main (void) {

    Matrix2x2 assistance_matrix (1, 1, 1, 0);
    int number = 0;


    std::cin >> number;


    Matrix2x2 result_matrix = assistance_matrix.pow (number - 1);


    std::cout << result_matrix.x12_;


    return 0;
}


//--------------------------------------------------


const Matrix2x2 Matrix2x2::E (1, 0, 0, 1);


Matrix2x2::Matrix2x2 (int x11, int x12, int x21, int x22):
        x11_ (x11),
        x12_ (x12),
        x21_ (x21),
        x22_ (x22) {}


Matrix2x2 Matrix2x2::pow (int n) {

    if (n < 0) { assert (false); return E; }


    if (!n) return E;


    if (n % 2 == 0) return pow (n / 2) * pow (n / 2);


    // n - odd
    return pow (n - 1) * (*this);
}


Matrix2x2 operator* (Matrix2x2 matrix1, Matrix2x2 matrix2) {

    int x11 = matrix1.x11_ * matrix2.x11_ + matrix1.x12_ * matrix2.x21_;
    int x12 = matrix1.x11_ * matrix2.x12_ + matrix1.x12_ * matrix2.x22_;
    int x21 = matrix1.x21_ * matrix2.x11_ + matrix1.x22_ * matrix2.x21_;
    int x22 = matrix1.x21_ * matrix2.x21_ + matrix1.x22_ * matrix2.x22_;

    x11 = x11 % 1000003;
    x12 = x12 % 1000003;
    x21 = x21 % 1000003;
    x22 = x22 % 1000003;


    return { x11, x12, x21, x22 };
}


