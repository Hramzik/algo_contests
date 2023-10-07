
//--------------------------------------------------

#include <iostream>
#include <cassert>
#include <limits.h>

//--------------------------------------------------

#include "d.hpp"

//--------------------------------------------------

static int binary_search_le (const std::vector <int>& vector, int start, int end, int value);

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
        array (),
        n (new_n),
        answer (),
        answer_len (0),
        dp (n, INT_MIN),
        pos (n, -1),
        prev (n, -1) {}

//--------------------------------------------------

void Solution::add_element (int element) {

    array.push_back (element);
}


void Solution::pre_solve (void) {

    //--------------------------------------------------
    // init dp

    dp [0] = INT_MAX;
}


void Solution::solve (void) {

    //--------------------------------------------------
    // count answer_len

    for (int i = 0; i < n; ++i) {

        // ищем, какую длину нам следует обновить
        int update_index = search_le_in_dp (array [i]);

        // если можем докинуть                 && нам это выгодно
        if (dp [update_index - 1] >= array [i] && array [i] >= dp [update_index]) {

            dp  [update_index] = array [i];
            pos [update_index] = i;
            prev [i] = pos [update_index - 1];

            answer_len = std::max (answer_len, update_index);
        }
    }

    //--------------------------------------------------
    // восстановление ответа

    int current_index = pos [answer_len];

    // раскручиваем цепочку добавлений
    while (current_index != -1) {

        answer.push_back (current_index);
        current_index = prev [current_index];
    }
}


void Solution::print_result (void) {

    std::cout << answer_len << "\n";

    // answer is reversed
    for (int i = 0; i < answer_len; ++i) {

        std::cout << answer [answer_len - 1 - i] + 1 << " ";
    }
}


int Solution::search_le_in_dp (int value) {

    return binary_search_le (dp, 0, n - 1, value);
}

static int binary_search_le (const std::vector <int>& vector, int start, int end, int value) {

    if (end - start < 0) { assert (0); return 0; }



    while (end - start > 0) {

        int center = (start + end) / 2;

        if (vector [center] <= value) end   = center;
        else                          start = center + 1;
    }


    return start;
}

