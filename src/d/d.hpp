#ifndef A_HPP_INCLUDED
#define A_HPP_INCLUDED
//--------------------------------------------------

#include <vector>

//--------------------------------------------------


class Solution {

  public:

    // исходный массив
    std::vector <int> array;
    // его размер
    int n;

    // ответ (в итоге получится реверснутым)
    std::vector <int> answer;
    // его размер
    int answer_len;

    // dp [i] - число, на которое оканчивается возрастающая последовательность длины i,
    // а если таких чисел несколько — то наименьшее из них
    std::vector <int> dp;

    // В pos[i] будем хранить индекс элемента,
    // на который заканчивается оптимальная подпоследовательность длины i,
    // а в prev[i] — позицию предыдущего элемента для a[i]

    std::vector <int> pos;
    std::vector <int> prev;

    //--------------------------------------------------

    Solution (int new_n);

    void add_element (int element);
    void pre_solve (void);
    void solve (void);
    void print_result (void);

    // returns result index
    int search_le_in_dp (int value);
};





//--------------------------------------------------
#endif