
//--------------------------------------------------

#include <cassert>

//--------------------------------------------------

#include "b.hpp"

//--------------------------------------------------


int main (void) {

    unsigned long long n = 0;
    Matrix5x5 assistance_matrix ({1, 1, 1, 1, 1,
                                  1, 0, 0, 0, 0,
                                  0, 1, 0, 0, 0,
                                  0, 0, 1, 0, 0,
                                  0, 0, 0, 1, 0});

    std::cin >> n;

    //--------------------------------------------------

    assistance_matrix.pow (n - 1);


    //std::cout << assistance_matrix;
    std::cout << get_answer (assistance_matrix);


    return 0;
}


//--------------------------------------------------


const Matrix5x5 Matrix5x5::UnitMatrix ({1, 0, 0, 0, 0,
                                        0, 1, 0, 0, 0,
                                        0, 0, 1, 0, 0,
                                        0, 0, 0, 1, 0,
                                        0, 0, 0, 0, 1});

const Matrix5x5 Matrix5x5::ZeroMatrix ({0, 0, 0, 0, 0,
                                        0, 0, 0, 0, 0,
                                        0, 0, 0, 0, 0,
                                        0, 0, 0, 0, 0,
                                        0, 0, 0, 0, 0});

//--------------------------------------------------

Matrix5x5::Matrix5x5 (std::vector <long long> elements):
        elements_ (elements) {}


void Matrix5x5::pow (unsigned long long n) {

    if (n < 0) { assert (0); return; }


    if (!n) {*this = E; return; }


    if (n % 2 == 0) {

        pow (n / 2);
        (*this) = (*this) * (*this);
        return;
    }


    // n - odd
    Matrix5x5 old_me = *this;
    pow (n - 1);
    (*this) = (*this) * old_me;
}


Matrix5x5 operator* (const Matrix5x5& lhs, const Matrix5x5& rhs) {
    //std::cout << lhs << rhs;

    Matrix5x5 result = Matrix5x5::O;

    for (int lhs_row = 0; lhs_row < 5; ++lhs_row) {

        for (int rhs_column = 0; rhs_column < 5; ++rhs_column) {

            long long mul_result = multiply_row_by_column (lhs, lhs_row, rhs, rhs_column);
            result.set (lhs_row, rhs_column, mul_result);
        }
    }


    return result;
}


long long multiply_row_by_column (const Matrix5x5& lhs, int lhs_row, const Matrix5x5& rhs, int rhs_column) {

    long long accumulator = 0;

    for (int i = 0; i < 5; ++i) {

        accumulator += lhs.get (lhs_row, i) * rhs.get (i, rhs_column);
        accumulator %= ANSWER_BY_MODULE;
    }


    return accumulator;
}


long long Matrix5x5::get (int row, int column) const {

    if    (row < 0 ||    row > 4) { assert (0); return 0; }
    if (column < 0 || column > 4) { assert (0); return 0; }


    return elements_ [row * 5 + column];
}


void Matrix5x5::set (int row, int column, long long value) {

    if    (row < 0 ||    row > 4) { assert (0); return; }
    if (column < 0 || column > 4) { assert (0); return; }


    elements_ [row * 5 + column] = value;
}


std::ostream& operator<< (std::ostream& stream, const Matrix5x5& matrix) {

    for (int row = 0; row < 5; ++row) {

        for (int column = 0; column < 5; ++column) {

            stream << matrix.get (row, column) << " ";
        }

        stream << "\n";
    }

    stream << "\n";


    return stream;
}


long long get_answer (const Matrix5x5& result) {

    return result.get (0, 0);
}


int pow (int value, int power) {

    if (!power) return 1;


    return pow (value, power - 1) * value;
}

