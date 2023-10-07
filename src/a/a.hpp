#ifndef A_HPP_INCLUDED
#define A_HPP_INCLUDED
//--------------------------------------------------


class Matrix2x2 {

  public:

    int x11_;
    int x12_;
    int x21_;
    int x22_;

    static const Matrix2x2 E;

    //--------------------------------------------------

    Matrix2x2 (int x11, int x12, int x21, int x22);

    Matrix2x2 pow (int n);
};


Matrix2x2 operator* (Matrix2x2 matrix1, Matrix2x2 matrix2);


//--------------------------------------------------
#endif