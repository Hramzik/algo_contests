
//--------------------------------------------------

#include <iostream>

//--------------------------------------------------

#include "task.hpp"

//--------------------------------------------------

int LcsFinder::bad_dp_value = -1;

//--------------------------------------------------

static void print_vector (std::vector <int>& vector);

//--------------------------------------------------

int main (void) {

    std::string string1;
    std::string string2;

    std::cin >> string1 >> string2;

    //--------------------------------------------------

    LcsFinder solver (string1, string2);

    //--------------------------------------------------

    auto result = solver.solve ();

    //--------------------------------------------------

    print_vector (result.m_first_sequence);
    std::cout << "\n";
    print_vector (result.m_second_sequence);

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

    //--------------------------------------------------

    find_lcs1 (static_cast <int> (string1_.size ()), static_cast <int> (string2_.size ()));
    find_lcs2 (static_cast <int> (string1_.size ()), static_cast <int> (string2_.size ()));
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

void LcsFinder::find_lcs1 (int prefix1, int prefix2) {

    if (!prefix1 || !prefix2) return;


    if (solver.get_dp_last_indexes (prefix1, prefix2) == Position (prefix1 - 1, prefix2 - 1)) {

        find_lcs1 (prefix1 - 1, prefix2 - 1);
        result.m_first_sequence.push_back (prefix1);
        return;
    }

    if (solver.get_dp_last_indexes (prefix1, prefix2) == Position (prefix1 - 1, prefix2)) {

        find_lcs1 (prefix1 - 1, prefix2);
        return;
    }


    find_lcs1 (prefix1, prefix2 - 1);
}

void LcsFinder::find_lcs2 (int prefix1, int prefix2) {

    if (!prefix1 || !prefix2) return;


    if (solver.get_dp_last_indexes (prefix1, prefix2) == Position (prefix1 - 1, prefix2 - 1)) {

        find_lcs2 (prefix1 - 1, prefix2 - 1);
        result.m_second_sequence.push_back (prefix2);
        return;
    }

    if (solver.get_dp_last_indexes (prefix1, prefix2) == Position (prefix1 - 1, prefix2)) {

        find_lcs2 (prefix1 - 1, prefix2);
        return;
    }


    find_lcs2 (prefix1, prefix2 - 1);
}

//--------------------------------------------------

LcsFinderResult::LcsFinderResult (void):
        m_first_sequence (),
        m_second_sequence () {}

//--------------------------------------------------

bool operator== (const Position& position1, const Position& position2) {

    if (position1.x_ != position2.x_) return false;
    if (position1.y_ != position2.y_) return false;


    return true;
}

//--------------------------------------------------

static void print_vector (std::vector <int>& vector) {

    for (int i = 0; i < vector.size (); ++i) {

        std::cout << vector [i] << " ";
    }
}

//--------------------------------------------------

