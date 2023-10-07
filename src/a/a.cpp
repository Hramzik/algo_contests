
//--------------------------------------------------

#include <iostream>
#include <cassert>

//--------------------------------------------------

#include "a.hpp"

//--------------------------------------------------


int main (void) {

    Matrix2x2 assistance_matrix (1, 1, 1, 0);
    long long number = 0;


    std::cin >> number;


    assistance_matrix.pow (number);


    std::cout << assistance_matrix.x22_;


    return 0;
}


//--------------------------------------------------


const Matrix2x2 Matrix2x2::E (1, 0, 0, 1);


Matrix2x2::Matrix2x2 (long long x11, long long x12, long long x21, long long x22):
        x11_ (x11),
        x12_ (x12),
        x21_ (x21),
        x22_ (x22) {}


void Matrix2x2::pow (long long n) {

    if (!n) {*this = E; return; }


    if (n % 2 == 0) {

        pow (n / 2);
        operator*= (*this);
        return;
    }


    // n - odd
    Matrix2x2 old_me = *this;
    pow (n - 1);
    operator*= (old_me);
}


void Matrix2x2::operator*= (Matrix2x2& rhs) {

    long long new_x11_ = (x11_ * rhs.x11_) % 1000003 + (x12_ * rhs.x21_) % 1000003;
    long long new_x12_ = (x11_ * rhs.x12_) % 1000003 + (x12_ * rhs.x22_) % 1000003;
    long long new_x21_ = (x21_ * rhs.x11_) % 1000003 + (x22_ * rhs.x21_) % 1000003;
    long long new_x22_ = (x21_ * rhs.x12_) % 1000003 + (x22_ * rhs.x22_) % 1000003;

    x11_ = new_x11_ % 1000003;
    x12_ = new_x12_ % 1000003;
    x21_ = new_x21_ % 1000003;
    x22_ = new_x22_ % 1000003;
}


