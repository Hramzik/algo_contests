#ifndef A_HPP_INCLUDED
#define A_HPP_INCLUDED
//--------------------------------------------------


class Matrix2x2 {

  public:

    long long x11_;
    long long x12_;
    long long x21_;
    long long x22_;

    static const Matrix2x2 E;

    //--------------------------------------------------

    Matrix2x2 (long long x11, long long x12, long long x21, long long x22);
    void operator*= (Matrix2x2& rhs);

    void pow (long long n);
};


//--------------------------------------------------
#endif