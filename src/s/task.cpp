
//--------------------------------------------------

#include <iostream>
#include <cassert>

//--------------------------------------------------

#include "task.hpp"

//--------------------------------------------------


int main (void) {

    int width = 0;
    int height = 0;
    std::cin >> width >> height;
    PatternCounter solution (width, height);

    //--------------------------------------------------

    solution.count_patterns ();

    //--------------------------------------------------

    std::cout << solution.get_answer ();

    //--------------------------------------------------

    return 0;
}


//--------------------------------------------------

PatternCounter::PatternCounter (int width, int height):
        width_  (std::max (width, height)),
        height_ (std::min (width, height)),

        profiles_count_ (1ull << height),

        transitions_ (profiles_count_ * profiles_count_, false),
        dp_          (width * profiles_count_, -1),

        answer_      (-1)
{
    init ();
}

//--------------------------------------------------

void PatternCounter::init (void) {

    for (Profile i = 0; i < profiles_count_; ++i) {

        set_dp (0, i, 1);
    }
}


void PatternCounter::count_patterns (void) {

    fill_transitions ();
    count_answer ();
}


int64_t PatternCounter::count_dp (int x, Profile profile) {

    uint64_t index = x * (profiles_count_) + profile;

    // already counted
    if (dp_ [index] != -1) return dp_ [index];

    //--------------------------------------------------

    dp_ [index] = 0;

    for (Profile prev = 0; prev < profiles_count_; ++prev) {

        if (!is_transition (profile, prev)) continue;

        dp_ [index] += count_dp (x - 1, prev);
    }


    return dp_ [index];
}


void PatternCounter::fill_transitions (void) {

    for (Profile i = 0; i < profiles_count_; ++i) {

        for (Profile j = 0; j < profiles_count_; ++j) {

            if (!is_transition (i, j)) continue;

            set_transition (i, j, true);
        }
    }
}


void PatternCounter::count_answer (void) {

    answer_ = 0;

    for (Profile profile = 0; profile < profiles_count_; ++profile) {

        answer_ += count_dp (width_ - 1, profile);
    }
}


bool PatternCounter::is_transition (Profile from, Profile to) {

    Profile black_match =   from  &   to;
    Profile   red_match = (~from) & (~to);

    black_match &= profiles_count_ - 1;
      red_match &= profiles_count_ - 1;

    //--------------------------------------------------

    if (black_match & (black_match << 1)) return false;
    if (  red_match & (  red_match << 1)) return false;


    return true;
}


bool PatternCounter::get_transition (Profile from, Profile to) {

    uint64_t index = from * (profiles_count_) + to;


    return transitions_ [index];
}


void PatternCounter::set_transition (Profile from, Profile to, bool value) {

    uint64_t index = from * (profiles_count_) + to;


    transitions_ [index] = value;
}


int64_t PatternCounter::get_dp (int x, Profile profile) {

    uint64_t index = x * (profiles_count_) + profile;


    return dp_ [index];
}


void PatternCounter::set_dp (int x, Profile profile, int64_t value) {

    uint64_t index = x * (profiles_count_) + profile;


    dp_ [index] = value;
}


int64_t PatternCounter::get_answer (void) {

    return answer_;
}

//--------------------------------------------------

