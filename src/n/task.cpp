
//--------------------------------------------------

#include <iostream>
#include <cassert>
#include <cmath>
#include <limits.h>

//--------------------------------------------------

#include "task.hpp"

//--------------------------------------------------


int main (void) {

    int ports_count = 0;
    int lines_count = 0;

    std::cin >> ports_count >> lines_count;

    Solution solution (ports_count, lines_count);

    //--------------------------------------------------

    Port port (0, 0, -1);

    for (int i = 0; i < ports_count; ++i) {

        std::cin >> port.x_ >> port.y_ >> port.flights_;
        port.flights_ %= ANSWER_BY_MODULE;
        solution.add_port (port);
    }

    int line = 0;

    for (int i = 0; i < lines_count; ++i) {

        std::cin >> line;
        solution.add_line (line);
    }

    //--------------------------------------------------

    solution.pre_solve ();
    solution.solve ();
    //solution.print_dp ();
    solution.print_result ();


    return 0;
}


//--------------------------------------------------

Port::Port (long long x, long long y, long long flights):
        x_       (x),
        y_       (y),
        flights_ (flights) {}

Solution::Solution (int ports_count, int lines_count):
        ports_count_ (ports_count),
        ports_       (),
        lines_count_ (lines_count),
        lines_       (),
        answer_      () {}

//--------------------------------------------------

void Solution::solve (void) {

    for (int i = 0; i < lines_count_; ++i) {

        long long line = lines_ [i];
        long long accumulator = 0;

        for (int j = 0; j < ports_count_; ++j) {

            //--------------------------------------------------
            // dp is needed for Fibonacci counting
            Matrix2x2 dp (1, 1, 1, 0);

            Port port = ports_ [j];
            long long port_height = port.y_ - port.x_;
            long long distance = port_height - line;

            if (distance < 0) continue;

            //--------------------------------------------------

            dp.pow (distance + 1);

            accumulator += (dp.x12_ * port.flights_) % ANSWER_BY_MODULE;
            accumulator %= ANSWER_BY_MODULE;
        }


        answer_.push_back (accumulator);
    }
}

void Solution::print_result (void) {

    for (int i = 0; i < static_cast <int> (answer_.size ()); ++i) {

        std::cout << answer_ [i] << "\n";
    }
}

void Solution::add_port (Port port) {

    ports_.push_back (port);
}

void Solution::add_line (long long line) {

    lines_.push_back (line);
}

//--------------------------------------------------
// Matrix code

const Matrix2x2 Matrix2x2::UnitMatrix (1, 0, 0, 1);

Matrix2x2::Matrix2x2 (long long x11, long long x12, long long x21, long long x22):
        x11_ (x11),
        x12_ (x12),
        x21_ (x21),
        x22_ (x22) {}


void Matrix2x2::pow (long long n) {

    if (!n) {*this = UnitMatrix; return; }


    if (n % 2 == 0) {

        pow (n / 2);
        operator*= (*this);
        return;
    }


    // n - odd
    Matrix2x2 old_me = *this;
    pow (n - 1);
    operator*= (old_me);
}


void Matrix2x2::operator*= (Matrix2x2& rhs) {

    long long new_x11_ = (x11_ * rhs.x11_) % ANSWER_BY_MODULE + (x12_ * rhs.x21_) % ANSWER_BY_MODULE;
    long long new_x12_ = (x11_ * rhs.x12_) % ANSWER_BY_MODULE + (x12_ * rhs.x22_) % ANSWER_BY_MODULE;
    long long new_x21_ = (x21_ * rhs.x11_) % ANSWER_BY_MODULE + (x22_ * rhs.x21_) % ANSWER_BY_MODULE;
    long long new_x22_ = (x21_ * rhs.x12_) % ANSWER_BY_MODULE + (x22_ * rhs.x22_) % ANSWER_BY_MODULE;

    x11_ = new_x11_ % ANSWER_BY_MODULE;
    x12_ = new_x12_ % ANSWER_BY_MODULE;
    x21_ = new_x21_ % ANSWER_BY_MODULE;
    x22_ = new_x22_ % ANSWER_BY_MODULE;
}

//--------------------------------------------------

