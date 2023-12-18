#ifndef CONTEST_HEADER_INCLUDED
#define CONTEST_HEADER_INCLUDED
//--------------------------------------------------

#include <vector>
#include <string>

//--------------------------------------------------

class Position {

  public:

    int x_;
    int y_;

    Position (int x, int y);
};


bool operator== (Position pair1, Position pair2);

//--------------------------------------------------

class LcsFinder {

    friend void print_result (LcsFinder& solver);
    friend void print_lcs1   (LcsFinder& solver, int prefix1, int prefix2);
    friend void print_lcs2   (LcsFinder& solver, int prefix1, int prefix2);

//--------------------------------------------------

  public:

    LcsFinder (std::string& string1, std::string& string2);

    void pre_solve (void);
    void solve (void);
    void print_result (void);

    void print_dp (void);

  private:

    std::string string1_;
    std::string string2_;

    static int bad_dp_value;
    std::vector <int> dp;
    std::vector <Position> dp_last_indexes;

    int answer_ = -1;

    //--------------------------------------------------

    void init (void);

    int count_dp (int prefix1_len, int prefix2_len);
    int   get_dp (int prefix1_len, int prefix2_len);
    void  set_dp (int prefix1_len, int prefix2_len, int value);

    Position get_dp_last_indexes (int prefix1_len, int prefix2_len);
    void set_dp_last_indexes (int prefix1_len, int prefix2_len, Position value);
};





//--------------------------------------------------
#endif