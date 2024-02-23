#ifndef CONTEST_HEADER_INCLUDED
#define CONTEST_HEADER_INCLUDED
//--------------------------------------------------

#include <vector>
#include <stdint.h>

//--------------------------------------------------

typedef uint64_t Profile;

//--------------------------------------------------

class PatternCounter {

  public:

    PatternCounter (int width, int height);

    //--------------------------------------------------

    void count_patterns (void);
    int64_t get_answer  (void);

  private:

    int width_;
    int height_;

    uint64_t              profiles_count_;
    std::vector <bool>    transitions_;
    std::vector <int64_t> dp_;

    int64_t answer_;

    //--------------------------------------------------

    void init (void);
    void fill_transitions (void);
    void count_answer     (void);

    bool  is_transition (Profile from, Profile to);
    bool get_transition (Profile from, Profile to);
    void set_transition (Profile from, Profile to, bool value);

    int64_t count_dp (int x, Profile profile);
    int64_t   get_dp (int x, Profile profile);
    void set_dp (int x, Profile profile, int64_t value);

    //--------------------------------------------------

};





//--------------------------------------------------
#endif