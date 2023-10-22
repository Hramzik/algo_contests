#ifndef CONTEST_HEADER_INCLUDED
#define CONTEST_HEADER_INCLUDED
//--------------------------------------------------

#include <vector>

//--------------------------------------------------

const int ANSWER_BY_MODULE = 1'000'000'000 + 9;

//--------------------------------------------------
// MATRIX CODE

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
// PORT CODE

class Port {

  public:

    long long x_;
    long long y_;

    long long flights_;

    Port (long long x, long long y, long long flights);
};


//--------------------------------------------------
// SOLUTION CODE

class Solution {

    int ports_count_;
    std::vector <Port> ports_;

    int lines_count_;
    std::vector <long long> lines_;

    std::vector <long long> answer_;

    //--------------------------------------------------

    int  recount_dp (int power, int min_number_power);
    int  get_dp     (int power, int min_number_power);
    void set_dp     (int power, int min_number_power, int value);

  public:

    Solution (int ports_count, int lines_count);

    void add_port (Port port);
    void add_line (long long line);

    void pre_solve (void);
    void solve (void);
    void print_result (void);
    void print_dp (void);

};





//--------------------------------------------------
#endif