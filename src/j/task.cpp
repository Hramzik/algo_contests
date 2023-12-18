
//--------------------------------------------------

#include <iostream>
#include <cassert>
#include <limits.h>
#include <iomanip>

//--------------------------------------------------

#include "task.hpp"

//--------------------------------------------------

int LcsFinder::bad_dp_value = -1;

//--------------------------------------------------

void print_result (LcsFinder& solver);
void print_lcs1   (LcsFinder& solver, int prefix1, int prefix2);
void print_lcs2   (LcsFinder& solver, int prefix1, int prefix2);

//--------------------------------------------------

int main (void) {

    std::string string1; std::cin >> string1;
    std::string string2; std::cin >> string2;
    LcsFinder solver (string1, string2);

    //--------------------------------------------------

    solver.solve ();

    //--------------------------------------------------

    print_result (solver);

    //--------------------------------------------------

    return 0;
}


//--------------------------------------------------

Position::Position (int x, int y):
        x_ (x),
        y_ (y) {}


LcsFinder::LcsFinder (std::string& string1, std::string& string2):
        string1_ (string1),
        string2_ (string2),
        dp (),
        dp_last_indexes ()
{
    init ();
}

//--------------------------------------------------

void LcsFinder::init (void) {

    for (int i = 0; i < (static_cast <int> (string1_.size ()) + 1) *
                        (static_cast <int> (string2_.size ()) + 1); ++i)
    {
        dp.push_back (bad_dp_value);
        dp_last_indexes.push_back ( { -1, -1 } );
    }

    //--------------------------------------------------

    for (int i = 0; i < static_cast <int> (string1_.size ()) + 1; ++i) {

        set_dp (i, 0, 0);
    }

    for (int i = 0; i < static_cast <int> (string2_.size ()) + 1; ++i) {

        set_dp (0, i, 0);
    }
}


void LcsFinder::solve (void) {

    answer_ = count_dp ((int) string1_.size (), (int) string2_.size ());
}


int LcsFinder::count_dp (int prefix1_len, int prefix2_len) {

    int index = prefix1_len * ((int) string2_.size () + 1) + prefix2_len;


    if (dp [index] != bad_dp_value) return dp [index];


    if (string1_ [prefix1_len - 1] == string2_ [prefix2_len - 1]) {

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


int LcsFinder::get_dp (int prefix1_len, int prefix2_len) {

    int index = prefix1_len * ((int) string2_.size () + 1) + prefix2_len;


    return dp [index];
}


void LcsFinder::set_dp (int prefix1_len, int prefix2_len, int value) {

    int index = prefix1_len * ((int) string2_.size () + 1) + prefix2_len;


    dp [index] = value;
}


Position LcsFinder::get_dp_last_indexes (int prefix1_len, int prefix2_len) {

    int index = prefix1_len * ((int) string2_.size () + 1) + prefix2_len;


    return dp_last_indexes [index];
}


void LcsFinder::set_dp_last_indexes (int prefix1_len, int prefix2_len, Position value) {

    int index = prefix1_len * ((int) string2_.size () + 1) + prefix2_len;


    dp_last_indexes [index] = value;
}


void print_result (LcsFinder& solver) {

    std::cout << solver.answer_ << "\n";

    print_lcs1 (solver, static_cast <int> (solver.string1_.size ()), static_cast <int> (solver.string2_.size ()));
    std::cout << "\n";
    print_lcs2 (solver, static_cast <int> (solver.string1_.size ()), static_cast <int> (solver.string2_.size ()));
}


void print_lcs1 (LcsFinder& solver, int prefix1, int prefix2) {

    if (!prefix1 || !prefix2) return;


    if (solver.get_dp_last_indexes (prefix1, prefix2) == Position (prefix1 - 1, prefix2 - 1)) {

        print_lcs1 (solver, prefix1 - 1, prefix2 - 1);
        std::cout << prefix1 << " ";
        return;
    }

    if (solver.get_dp_last_indexes (prefix1, prefix2) == Position (prefix1 - 1, prefix2)) {

        print_lcs1 (solver, prefix1 - 1, prefix2);
        return;
    }


    print_lcs1 (solver, prefix1, prefix2 - 1);
}


void print_lcs2 (LcsFinder& solver, int prefix1, int prefix2) {

    if (!prefix1 || !prefix2) return;


    if (solver.get_dp_last_indexes (prefix1, prefix2) == Position (prefix1 - 1, prefix2 - 1)) {

        print_lcs2 (solver, prefix1 - 1, prefix2 - 1);
        std::cout << prefix2 << " ";
        return;
    }

    if (solver.get_dp_last_indexes (prefix1, prefix2) == Position (prefix1 - 1, prefix2)) {

        print_lcs2 (solver, prefix1 - 1, prefix2);
        return;
    }


    print_lcs2 (solver, prefix1, prefix2 - 1);
}


void LcsFinder::print_dp (void) {

    for (int i = 0; i < (int) string1_.size () + 1; ++i) {

        for (int j = 0; j < (int) string2_.size () + 1; ++j) {

            std::cout << std::setw (2) << get_dp (i, j) << " ";
        }

        std::cout << "\n";
    }
}


bool operator== (Position pair1, Position pair2) {

    if (pair1.x_ != pair2.x_) return false;
    if (pair1.y_ != pair2.y_) return false;


    return true;
}

