#ifndef CONTEST_HEADER_INCLUDED
#define CONTEST_HEADER_INCLUDED
//--------------------------------------------------

#include <vector>
#include <cstdint>

//--------------------------------------------------

const int ANSWER_BY_MODULE = 1'000'000'000 + 9;

//--------------------------------------------------
// MATRIX CODE

class Matrix2x2 {

  public:

    static const Matrix2x2 UnitMatrix;

    //--------------------------------------------------

    Matrix2x2 (int64_t x11, int64_t x12, int64_t x21, int64_t x22);

    //--------------------------------------------------

    Matrix2x2& operator*= (const Matrix2x2& rhs);
    void pow (int64_t n);

    //--------------------------------------------------

    int64_t x11_;
    int64_t x12_;
    int64_t x21_;
    int64_t x22_;
};


//--------------------------------------------------
// PORT CODE

class Port {

  public:

    int64_t x_;
    int64_t y_;

    int64_t flights_;

    Port (int64_t x, int64_t y, int64_t flights);
};


//--------------------------------------------------
// SOLUTION CODE

class TravelCounter {

  public:

    TravelCounter (int ports_count, int lines_count);

    void add_port (Port port);
    void add_line (int64_t line);

    void                   solve      (void);
    std::vector <int64_t>& get_answer (void);

  private:

    int ports_count_;
    std::vector <Port> ports_;

    int lines_count_;
    std::vector <int64_t> lines_;

    std::vector <int64_t> answer_;

    //--------------------------------------------------

    int  recount_dp (int power, int min_number_power);
    int  get_dp     (int power, int min_number_power);
    void set_dp     (int power, int min_number_power, int value);
};





//--------------------------------------------------
#endif