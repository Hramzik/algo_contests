#ifndef CONTEST_HEADER_INCLUDED
#define CONTEST_HEADER_INCLUDED
//--------------------------------------------------

#include <vector>

//--------------------------------------------------


class Solution {

    int max_power_;
    long long answer_;

    std::vector <int> dp;

    //--------------------------------------------------

    int  recount_dp (int power, int min_number_power);
    int  get_dp     (int power, int min_number_power);
    void set_dp     (int power, int min_number_power, int value);

  public:

    Solution (int power);

    void pre_solve (void);
    void solve (void);
    void print_result (void);
    void print_dp (void);

};





//--------------------------------------------------
#endif