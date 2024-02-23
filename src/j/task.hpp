#ifndef CONTEST_HEADER_INCLUDED
#define CONTEST_HEADER_INCLUDED
//--------------------------------------------------

#include <vector>
#include <string>

//--------------------------------------------------

class Position {

  public:

    int x_;
    int y_;

    Position (int x, int y);
};


bool operator== (const Position& position1, const Position& position2);

//--------------------------------------------------

class LcsFinder {

  public:

    LcsFinder (std::string& string1, std::string& string2);

    LcsFinderResult solve (void);

  private:

    std::string string1_;
    std::string string2_;

    static int bad_dp_value;
    std::vector <int> dp;
    std::vector <Position> dp_last_indexes;

    int answer_ = -1;
    LcsFinderResult result;

    //--------------------------------------------------

    void init (void);

    int count_dp (int prefix1_len, int prefix2_len);
    int   get_dp (int prefix1_len, int prefix2_len);
    void  set_dp (int prefix1_len, int prefix2_len, int value);

    Position get_dp_last_indexes (int prefix1_len, int prefix2_len);
    void set_dp_last_indexes (int prefix1_len, int prefix2_len, Position value);

    //--------------------------------------------------

    void find_lcs1 (int prefix1, int prefix2);
    void find_lcs2 (int prefix1, int prefix2);
};

//--------------------------------------------------

class LcsFinderResult {

  public:

    LcsFinderResult (void);

    //--------------------------------------------------

    std::vector <int> m_first_sequence;
    std::vector <int> m_second_sequence;
}


//--------------------------------------------------
#endif