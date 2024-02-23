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

class Edge {

  public:

    Edge (int vertex1, int vertex2, int weight);

    //--------------------------------------------------

    int m_vertex1;
    int m_vertex2;
    int m_weight;
};

class Neighbor {

  public:

    Neighbor (int vertex, int weight);

    //--------------------------------------------------

    int m_vertex;
    int m_weight;
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

class KSSFinder {

  public:

    KSSFinder (const Graph& graph);

    //--------------------------------------------------

    std::vector <int> solve (void);

//--------------------------------------------------

  private:

    void dfs        (int vertex_index);
    void rgraph_dfs (int vertex_index);

    //--------------------------------------------------

    std::vector <int> m_kss_indexes;
    int current_kss;

    const Graph& m_graph;
    const Graph  m_rgraph;

    std::vector <Color> m_graph_dfs_colors;
    std::vector <Color> m_rgraph_dfs_colors;

    // by rgraph dfs leave time
    std::vector <int> reordered_vertexes;
};

//--------------------------------------------------
#endif