
//--------------------------------------------------

#include <iostream>

//--------------------------------------------------

#include "task.hpp"

//--------------------------------------------------

static void print_result (TravelCounter& solver);

//--------------------------------------------------

int main (void) {

    int ports_count = 0;
    int lines_count = 0;

    std::cin >> ports_count >> lines_count;

    TravelCounter solution (ports_count, lines_count);

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

    solution.solve ();

    //--------------------------------------------------

    print_result (solution);

    //--------------------------------------------------

    return 0;
}

static void print_result (TravelCounter& solver) {

    std::vector <int64_t>& answer = solver.get_answer ();

    //--------------------------------------------------

    for (int i = 0; i < static_cast <int> (answer.size ()); ++i) {

        std::cout << answer [i] << "\n";
    }
}

//--------------------------------------------------

Port::Port (int64_t x, int64_t y, int64_t flights):
        x_       (x),
        y_       (y),
        flights_ (flights) {}

TravelCounter::TravelCounter (int ports_count, int lines_count):
        ports_count_ (ports_count),
        ports_       (),
        lines_count_ (lines_count),
        lines_       (),
        answer_      () {}

//--------------------------------------------------

void TravelCounter::solve (void) {

    for (int i = 0; i < lines_count_; ++i) {

        int64_t line = lines_ [i];
        int64_t accumulator = 0;

        for (int j = 0; j < ports_count_; ++j) {

            //--------------------------------------------------
            // dp is needed for Fibonacci counting
            Matrix2x2 dp (1, 1, 1, 0);

            Port port = ports_ [j];
            int64_t port_height = port.y_ - port.x_;
            int64_t distance = port_height - line;

            if (distance < 0) continue;

            //--------------------------------------------------

            dp.pow (distance + 1);

            accumulator += (dp.x12_ * port.flights_) % ANSWER_BY_MODULE;
            accumulator %= ANSWER_BY_MODULE;
        }


        answer_.push_back (accumulator);
    }
}

std::vector <int64_t>& TravelCounter::get_answer (void) {

    return answer_;
}

void TravelCounter::add_port (Port port) {

    ports_.push_back (port);
}

void TravelCounter::add_line (int64_t line) {

    lines_.push_back (line);
}

//--------------------------------------------------
// Matrix code

const Matrix2x2 Matrix2x2::UnitMatrix (1, 0, 0, 1);

Matrix2x2::Matrix2x2 (int64_t x11, int64_t x12, int64_t x21, int64_t x22):
        x11_ (x11),
        x12_ (x12),
        x21_ (x21),
        x22_ (x22) {}

void Matrix2x2::pow (int64_t n) {

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

Matrix2x2& Matrix2x2::operator*= (const Matrix2x2& rhs) {

    int64_t new_x11_ = (x11_ * rhs.x11_) % ANSWER_BY_MODULE + (x12_ * rhs.x21_) % ANSWER_BY_MODULE;
    int64_t new_x12_ = (x11_ * rhs.x12_) % ANSWER_BY_MODULE + (x12_ * rhs.x22_) % ANSWER_BY_MODULE;
    int64_t new_x21_ = (x21_ * rhs.x11_) % ANSWER_BY_MODULE + (x22_ * rhs.x21_) % ANSWER_BY_MODULE;
    int64_t new_x22_ = (x21_ * rhs.x12_) % ANSWER_BY_MODULE + (x22_ * rhs.x22_) % ANSWER_BY_MODULE;

    x11_ = new_x11_ % ANSWER_BY_MODULE;
    x12_ = new_x12_ % ANSWER_BY_MODULE;
    x21_ = new_x21_ % ANSWER_BY_MODULE;
    x22_ = new_x22_ % ANSWER_BY_MODULE;

    //--------------------------------------------------

    return *this;
}

//--------------------------------------------------

