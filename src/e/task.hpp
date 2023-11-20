#ifndef CONTEST_HEADER_INCLUDED
#define CONTEST_HEADER_INCLUDED
//--------------------------------------------------

#include <iostream>
#include <vector>
#include <set>

//--------------------------------------------------

class Vertex_Info;

//--------------------------------------------------

enum Color {

    WHITE,
    BLACK,
};


//--------------------------------------------------


class Neighbor_Info {

  public:

    Neighbor_Info (Vertex_Info* neighbor, int edge_index);

    //--------------------------------------------------

    bool operator< (const Neighbor_Info& other) const;
 
//--------------------------------------------------

    Vertex_Info* m_neighbor;
    int          m_edge_index;
};


class Vertex_Info {

  public:

    Vertex_Info (int number);

//--------------------------------------------------

    int m_index;
    Color m_color;
    std::set <Neighbor_Info> m_neighbors;
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

    void dfs (int vertex_index, int edge_index);

    //--------------------------------------------------

    std::vector <int> m_bridges;

    int m_vertex_count;
    int m_edges_count;
    std::vector <Vertex_Info> m_graph;

    int dfs_timer;
    std::vector <int> m_enter_times;
    std::vector <int> m_least_deep_accesible;
};


//--------------------------------------------------

std::ostream& operator<< (std::ostream& ostream, std::vector <int> vector);

//--------------------------------------------------
#endif