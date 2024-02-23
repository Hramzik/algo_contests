#ifndef CONTEST_HEADER_INCLUDED
#define CONTEST_HEADER_INCLUDED
//--------------------------------------------------

#include <iostream>
#include <vector>
#include <set>

//--------------------------------------------------

enum Color {

    WHITE,
    BLACK,
};

//--------------------------------------------------

class Edge {

  public:

    Edge (int vertex1, int vertex2, int edge_index);

    //--------------------------------------------------

    int m_vertex1;
    int m_vertex2;
    int m_edge_index;
};

class Neighbor {

  public:

    Neighbor (int vertex, int edge_index);

    //--------------------------------------------------

    int m_vertex;
    int m_edge_index;
};

class Graph {

  public:

    Graph (int vertex_count);

    //--------------------------------------------------

    void  add_adge (Edge edge);
    Graph get_rgraph (void);

  //private:

    int                                  m_vertex_count;
    std::vector <Edge>                   m_edges;
    std::vector <std::vector <Neighbor>> m_neighbors;
};

//--------------------------------------------------

class Bridges_Finder {

  public:

    Bridges_Finder (const Graph& graph);

    //--------------------------------------------------

    void solve (void);

//--------------------------------------------------

  private:

    void dfs (int vertex_index, int edge_index);

    //--------------------------------------------------

    std::vector <int> m_bridges;

    const Graph&        m_graph;
    std::vector <Color> m_dfs_colors;

    int dfs_timer;
    std::vector <int> m_enter_times;
    std::vector <int> m_least_deep_accesible;
};


//--------------------------------------------------

std::ostream& operator<< (std::ostream& ostream, std::vector <int> vector);

//--------------------------------------------------
#endif