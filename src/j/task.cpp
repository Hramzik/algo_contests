
//--------------------------------------------------

#include <iostream>
#include <cassert>
#include <limits.h>
#include <iomanip>

//--------------------------------------------------

#include "task.hpp"

//--------------------------------------------------


int main (void) {

    Solution solution;
    solution.read_data ();



    solution.pre_solve ();
    solution.solve ();
    //solution.print_dp ();
    solution.print_result ();


    return 0;
}


//--------------------------------------------------

Int_Pair::Int_Pair (int x, int y):
        x_ (x),
        y_ (y) {}


Solution::Solution ():
        string1 (),
        string2 (),
        dp (),
        dp_last_indexes () {}

//--------------------------------------------------

void Solution::read_data (void) {

    std::cin >> string1 >> string2;
}


void Solution::pre_solve (void) {

    for (int i = 0; i < ((int) string1.size () + 1) * ((int) string2.size () + 1); ++i) {

        dp.push_back (-1);
        dp_last_indexes.push_back ( { -1, -1 } );
    }

    //--------------------------------------------------

    for (int i = 0; i < (int) string1.size () + 1; ++i) {

        set_dp (i, 0, 0);
    }

    for (int i = 0; i < (int) string2.size () + 1; ++i) {

        set_dp (0, i, 0);
    }
}


void Solution::solve (void) {

    answer_ = count_dp ((int) string1.size (), (int) string2.size ());
}


int Solution::count_dp (int prefix1_len, int prefix2_len) {

    int index = prefix1_len * ((int) string2.size () + 1) + prefix2_len;


    if (dp [index] != -1) return dp [index];


    if (string1 [prefix1_len - 1] == string2 [prefix2_len - 1]) {

        dp [index] = count_dp (prefix1_len - 1, prefix2_len - 1) + 1;

        set_dp_last_indexes (prefix1_len, prefix2_len,
                { prefix1_len - 1, prefix2_len - 1});

        return dp [index];
    }


    // разные символы
    int result = count_dp (prefix1_len - 1, prefix2_len);
    set_dp_last_indexes (prefix1_len, prefix2_len,
                { prefix1_len - 1, prefix2_len});

    int alternative = count_dp (prefix1_len, prefix2_len - 1);

    if (result < alternative) {

        result = alternative;
        set_dp_last_indexes (prefix1_len, prefix2_len,
                { prefix1_len, prefix2_len - 1});
    }


    dp [index] = result;


    return dp [index];
}


int Solution::get_dp (int prefix1_len, int prefix2_len) {

    int index = prefix1_len * ((int) string2.size () + 1) + prefix2_len;


    return dp [index];
}


void Solution::set_dp (int prefix1_len, int prefix2_len, int value) {

    int index = prefix1_len * ((int) string2.size () + 1) + prefix2_len;


    dp [index] = value;
}


Int_Pair Solution::get_dp_last_indexes (int prefix1_len, int prefix2_len) {

    int index = prefix1_len * ((int) string2.size () + 1) + prefix2_len;


    return dp_last_indexes [index];
}


void Solution::set_dp_last_indexes (int prefix1_len, int prefix2_len, Int_Pair value) {

    int index = prefix1_len * ((int) string2.size () + 1) + prefix2_len;


    dp_last_indexes [index] = value;
}


void Solution::print_result (void) {

    std::cout << answer_ << "\n";

    print_lcs1 ((int) string1.size (), (int) string2.size ());
    std::cout << "\n";
    print_lcs2 ((int) string1.size (), (int) string2.size ());
}


void Solution::print_lcs1 (int prefix1, int prefix2) {

    if (!prefix1 || !prefix2) return;


    if (get_dp_last_indexes (prefix1, prefix2) == Int_Pair (prefix1 - 1, prefix2 - 1)) {

        print_lcs1 (prefix1 - 1, prefix2 - 1);
        std::cout << prefix1 << " ";
        return;
    }

    if (get_dp_last_indexes (prefix1, prefix2) == Int_Pair (prefix1 - 1, prefix2)) {

        print_lcs1 (prefix1 - 1, prefix2);
        return;
    }


    print_lcs1 (prefix1, prefix2 - 1);
}


void Solution::print_lcs2 (int prefix1, int prefix2) {

    if (!prefix1 || !prefix2) return;


    if (get_dp_last_indexes (prefix1, prefix2) == Int_Pair (prefix1 - 1, prefix2 - 1)) {

        print_lcs2 (prefix1 - 1, prefix2 - 1);
        std::cout << prefix2 << " ";
        return;
    }

    if (get_dp_last_indexes (prefix1, prefix2) == Int_Pair (prefix1 - 1, prefix2)) {

        print_lcs2 (prefix1 - 1, prefix2);
        return;
    }


    print_lcs2 (prefix1, prefix2 - 1);
}


void Solution::print_dp (void) {

    for (int i = 0; i < (int) string1.size () + 1; ++i) {

        for (int j = 0; j < (int) string2.size () + 1; ++j) {

            std::cout << std::setw (2) << get_dp (i, j) << " ";
        }

        std::cout << "\n";
    }
}


bool operator== (Int_Pair pair1, Int_Pair pair2) {

    if (pair1.x_ != pair2.x_) return false;
    if (pair1.y_ != pair2.y_) return false;


    return true;
}

