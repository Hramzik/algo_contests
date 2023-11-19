#ifndef CONTEST_HEADER_INCLUDED
#define CONTEST_HEADER_INCLUDED
//--------------------------------------------------

#include <vector>
#include <set>

//--------------------------------------------------

enum Color {

    WHITE,
    BLACK,
};


//--------------------------------------------------


class Vertex_Info {

  public:

    Vertex_Info (int number);

//--------------------------------------------------

    int m_index;
    Color m_color;
    std::set <Vertex_Info*> m_neighbors;
};


//--------------------------------------------------


class Solution {

  public:

    Solution (int vertex_count);

    //--------------------------------------------------

    void add_edge (int vertex1, int vertex2);

    void pre_solve (void);
    void solve (void);
    void print_result (void);

//--------------------------------------------------

  private:

    void dfs        (int vertex_index);
    void rgraph_dfs (int vertex_index);

    //--------------------------------------------------

    std::vector <int> m_kss_indexes;
    int current_kss;

    int m_vertex_count;
    std::vector <Vertex_Info> m_graph;
    std::vector <Vertex_Info> m_rgraph;

    // by rgraph dfs leave time
    std::vector <int> reordered_vertexes;
};


//--------------------------------------------------
#endif