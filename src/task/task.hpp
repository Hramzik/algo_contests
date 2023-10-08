#ifndef CONTEST_HEADER_INCLUDED
#define CONTEST_HEADER_INCLUDED
//--------------------------------------------------

#include <vector>
#include <string>

//--------------------------------------------------

class Int_Pair {

  public:

    int x_;
    int y_;

    Int_Pair (int x, int y);

};


bool operator== (Int_Pair pair1, Int_Pair pair2);

//--------------------------------------------------

class Solution {

    std::string string1;
    std::string string2;

    std::vector <int>      dp;
    std::vector <Int_Pair> dp_last_indexes;

    int answer_ = -1;

    //--------------------------------------------------

    int count_dp (int prefix1_len, int prefix2_len);
    int   get_dp (int prefix1_len, int prefix2_len);
    void  set_dp (int prefix1_len, int prefix2_len, int value);

    Int_Pair get_dp_last_indexes (int prefix1_len, int prefix2_len);
    void set_dp_last_indexes (int prefix1_len, int prefix2_len, Int_Pair value);

    void print_lcs1 (int prefix1, int prefix2);
    void print_lcs2 (int prefix1, int prefix2);

  public:

    Solution (void);

    void read_data (void);

    void pre_solve (void);
    void solve (void);
    void print_result (void);

    void print_dp (void);

};





//--------------------------------------------------
#endif