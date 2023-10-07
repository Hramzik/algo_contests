
//--------------------------------------------------

#include <iostream>
#include <cassert>
#include <limits.h>

//--------------------------------------------------

#include "d.hpp"

//--------------------------------------------------


int main (void) {

    int n = 0;
    std::cin >> n;
    Solution solution (n);

    for (int i = 0; i < n; ++i) {

        int new_element = 0;
        std::cin >> new_element;
        solution.add_element (new_element);
    }


    solution.pre_solve ();
    solution.solve ();
    solution.print_result ();


    return 0;
}


//--------------------------------------------------

Solution::Solution (int new_n):

//--------------------------------------------------

void Solution::solve (void) {

    
}


void Solution::print_result (void) {

    
}

