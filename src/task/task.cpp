
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

Solution::Solution (int max_power):
        max_power_ (max_power),
        answer_ (-1),
        dp ((max_power + 1) * (max_power + 1), -1) {}

//--------------------------------------------------

void Solution::pre_solve (void) {

    for (int i = 1; i <= max_power_; ++i) {

        set_dp (i, i, 1); // count is 1 when total power == minimal power
    }
}


void Solution::solve (void) {

    answer_ = 0;

    for (int i = 1; i <= max_power_; ++i) {

        answer_ += recount_dp (max_power_, i);
    }
}


int Solution::recount_dp (int power, int min_number_power) {

    int index = power * (max_power_ + 1) + min_number_power;


    // уже посчитано
    if (dp [index] != -1) return dp [index];


    // ща пощитаем..
    dp [index] = 0;

    // перебираем возможные суффиксы
    int suffix_power = power - min_number_power;
    if (suffix_power < 1) { dp [index] = 0; return 0; }

    for (int min_suffix_power = 2 * min_number_power; min_suffix_power <= suffix_power;
                                                      ++min_suffix_power) {

        dp [index] += recount_dp (suffix_power, min_suffix_power);
    }


    if (dp [index] == -1) dp [index] = 0;


    return dp [index];
}


int Solution::get_dp (int power, int min_number_power) {

    int index = power * (max_power_ + 1) + min_number_power;


    return dp [index];
}


void Solution::set_dp (int power, int min_number_power, int value) {

    int index = power * (max_power_ + 1) + min_number_power;

    dp [index] = value;
}


void Solution::print_result (void) {

    std::cout << answer_;
}


void Solution::print_dp (void) {

    for (int power = 1; power <= max_power_; ++power) {

        for (int min_number_power = 1; min_number_power <= max_power_;
                                       ++min_number_power) {

            std::cout << get_dp (power, min_number_power) << " ";
        }

        std::cout << "\n";
    }
}
