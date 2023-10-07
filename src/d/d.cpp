
//--------------------------------------------------

#include <iostream>
#include <cassert>

//--------------------------------------------------

#include "d.hpp"

//--------------------------------------------------

static int binary_search_le (std::vector <int> vector, int start, int end, int value);

//--------------------------------------------------


int main (void) {

    Solution solution;

    int n = 0;
    std::cin >> n;

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

Solution::Solution (void):
        array (),
        n (0),
        answer (),
        answer_len (0),
        dp (),
        pos (),
        prev () {}

//--------------------------------------------------

void Solution::add_element (int element) {

    array.push_back (element);
    n = (int) array.size ();
}


void Solution::pre_solve (void) {

    //--------------------------------------------------
    // init dp

    dp.push_back (INT_MAX);

    for (int i = 0; i < n - 1; ++i) {

        dp.push_back (INT_MIN);
    }

    //--------------------------------------------------
    // init pos and prev

    for (int i = 0; i < n; ++i) {

        prev.push_back (-1);
        pos.push_back  (-1);
    }
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

static int binary_search_le (std::vector <int> vector, int start, int end, int value) {

    if (end - start < 0) { assert (0); return 0; }


    if (end - start == 0) return start;


    int center = (start + end) / 2;

    if (vector [center] <= value) return binary_search_le (vector, start, center, value);
    return binary_search_le (vector, center + 1, end, value);
}

