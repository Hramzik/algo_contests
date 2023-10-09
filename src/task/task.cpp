
//--------------------------------------------------

#include <iostream>
#include <cassert>
#include <limits.h>

//--------------------------------------------------

#include "task.hpp"

//--------------------------------------------------


int main (void) {

    int max_power = 0;
    std::cin >> max_power;
    Solution solution (max_power);



    solution.pre_solve ();
    solution.solve ();
    //solution.print_dp ();
    solution.print_result ();


    return 0;
}


//--------------------------------------------------

Solution::Solution (int ports_count, int lines_count):
        ports_count_ (ports_count),
        ports_       (),
        lines_count_ (lines_count),
        lines_       (),
        answer_      () {}

//--------------------------------------------------

void Solution::pre_solve (void) {

    
}


void Solution::solve (void) {

    
}




void Solution::print_result (void) {

    for (int i = 0; i < answer_.size (); ++i) {

        std::cout << answer_ [i] << "\n";
    }
}

/*
void Solution::print_dp (void) {

    for (int power = 1; power <= max_power_; ++power) {

        for (int min_number_power = 1; min_number_power <= max_power_;
                                       ++min_number_power) {

            std::cout << get_dp (power, min_number_power) << " ";
        }

        std::cout << "\n";
    }
}
*/


void Solution::add_port (long long port) {

    ports_.push_back (port);
}


void Solution::add_line (long long line) {

    lines_.push_back (line);
}

/*
int Solution::recount_dp (int power, int min_number_power) {

    int index = power * (max_power_ + 1) + min_number_power;


    


    return dp [index];
}


int Solution::get_dp (int power, int min_number_power) {

    int index = power * (max_power_ + 1) + min_number_power;


    return dp [index];
}


void Solution::set_dp (int power, int min_number_power, int value) {

    int index = power * (max_power_ + 1) + min_number_power;

    dp [index] = value;
}*/