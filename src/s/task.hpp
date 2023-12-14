#ifndef CONTEST_HEADER_INCLUDED
#define CONTEST_HEADER_INCLUDED
//--------------------------------------------------

#include <vector>
#include <stdint.h>

//--------------------------------------------------

typedef uint64_t Profile;

//--------------------------------------------------

class Solution {

  public:

    Solution (int width, int height);

    //--------------------------------------------------

    void pre_solve (void);
    void solve (void);
    void print_result (void);

    void print_transitions (void);
    void print_dp          (void);

  private:

    int width_;
    int height_;

    ULL profiles_count_;
    std::vector <bool> transitions_;
    std::vector <LL>   dp_;

    LL answer_;

    void fill_transitions (void);
    void count_answer     (void);

    bool  is_transition (Profile from, Profile to);
    bool get_transition (Profile from, Profile to);
    void set_transition (Profile from, Profile to, bool value);

    LL count_dp (int x, Profile profile);
    LL   get_dp (int x, Profile profile);
    void set_dp (int x, Profile profile, LL value);

    //--------------------------------------------------

};





//--------------------------------------------------
#endif