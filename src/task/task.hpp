#ifndef CONTEST_HEADER_INCLUDED
#define CONTEST_HEADER_INCLUDED
//--------------------------------------------------

#include <vector>

//--------------------------------------------------


class Solution {

    int ports_count_;
    std::vector <long long> ports_;

    int lines_count_;
    std::vector <long long> lines_;

    std::vector <int> answer_;

    //--------------------------------------------------

    int  recount_dp (int power, int min_number_power);
    int  get_dp     (int power, int min_number_power);
    void set_dp     (int power, int min_number_power, int value);

  public:

    Solution (int ports_count, int lines_count);

    void add_port (long long port);
    void add_line (long long line);

    void pre_solve (void);
    void solve (void);
    void print_result (void);
    void print_dp (void);

};





//--------------------------------------------------
#endif