#ifndef B_HPP_INCLUDED
#define B_HPP_INCLUDED
//--------------------------------------------------

#include <vector>
#include <iostream>

//--------------------------------------------------


const int ANSWER_BY_MODULE = 1000003;


class Matrix5x5 {

  public:

    std::vector <long long> elements_;

    //--------------------------------------------------

    static const Matrix5x5 O;
    static const Matrix5x5 E;

    //--------------------------------------------------

    Matrix5x5 (std::vector <long long> elements);

    void pow (unsigned long long n);

    long long get (int row, int column) const;
    void      set (int row, int column, long long value);
};

//--------------------------------------------------

Matrix5x5 operator* (const Matrix5x5& lhs, const Matrix5x5& rhs);

long long multiply_row_by_column (const Matrix5x5& lhs, int lhs_row,
                                  const Matrix5x5& rhs, int rhs_column);

long long get_answer (const Matrix5x5& result);

std::ostream& operator<< (std::ostream& stream, const Matrix5x5& matrix);

//--------------------------------------------------

int pow (int value, int power);


//--------------------------------------------------
#endif