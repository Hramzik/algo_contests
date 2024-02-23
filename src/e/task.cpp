

//--------------------------------------------------

#include <cassert>
#include <algorithm>

//--------------------------------------------------

#ifndef CONTEST_HEADER_INCLUDED
    #include "task.hpp"
#endif

//--------------------------------------------------


int main (void) {

    int vertex_count = 0;
    std::cin >> vertex_count;

    Graph graph (vertex_count);

    //--------------------------------------------------

    int edges_count  = 0;
    std::cin >> edges_count;

    int vertex1 = 0;
    int vertex2 = 0;

    for (int i = 0; i < edges_count; ++i) {

        std::cin >> vertex1 >> vertex2;
        graph.add_edge (vertex1, vertex2, i);
    }

    //--------------------------------------------------

    Bridges_Finder solution (vertex_count);

    std::vector <int> bridges = solution.solve ();
    std::cout << bridges.size () << bridges;

    //--------------------------------------------------

    return 0;
}


//--------------------------------------------------

Bridges_Finder::Bridges_Finder (const Graph& graph):

        m_bridges (),

        m_graph (graph),

        dfs_timer (0),
        m_enter_times          (graph.m_vertex_count, -1),
        m_least_deep_accesible (graph.m_vertex_count, -1) {}

//--------------------------------------------------

std::vector <int> Bridges_Finder::solve (void) {

    for (int i = 0; i < m_graph.m_vertex_count; ++i) {

        if (m_dfs_colors [i] != WHITE) continue;

        dfs (i, -1);
    }

    //--------------------------------------------------

    std::sort (m_bridges.begin (), m_bridges.end ());

    //--------------------------------------------------

    return m_bridges;
}

//--------------------------------------------------

void Bridges_Finder::dfs (int vertex_index, int edge_index) {

    int& least_deep_accesible = m_least_deep_accesible [vertex_index];
    int& enter_time           = m_enter_times          [vertex_index];

    //--------------------------------------------------

    enter_time           = dfs_timer;
    least_deep_accesible = dfs_timer;
    ++dfs_timer;

    //--------------------------------------------------

    vertex.m_color = BLACK;

    for (Neighbor neighbor : m_graph.m_neighbors [vertex_index]) {

        int next_vertex = neighbor.m_vertex;

        if (neighbor.m_edge_index == edge_index) continue;

        if (m_dfs_colors [next_vertex] != WHITE) {

            least_deep_accesible = std::min (least_deep_accesible, m_enter_times [next_vertex]);
            continue;
        }

        //--------------------------------------------------

        dfs (next_vertex, neighbor.m_edge_index);

        least_deep_accesible = std::min (least_deep_accesible, m_least_deep_accesible [next_vertex]);

        //--------------------------------------------------
        // не могу вернуться из ребенка

        if (m_least_deep_accesible [next_vertex] > enter_time) {

            m_bridges.push_back (neighbor.m_edge_index);
        }
    }
}

//--------------------------------------------------
// GRAPH CODE

Edge::Edge (int vertex1, int vertex2, int edge_index):
        m_vertex1 (vertex1),
        m_vertex2 (vertex2),
        m_edge_index  (edge_index) {}

//--------------------------------------------------

Neighbor::Neighbor (int vertex, int edge_index):
        m_vertex     (vertex),
        m_edge_index (edge_index) {}

//--------------------------------------------------

Graph::Graph (int vertex_count):

        m_vertex_count (vertex_count),
        m_edges (),
        m_neighbors (vertex_count) {}

void Graph::add_adge (Edge edge) {

    m_edges.push_back (edge);

    //--------------------------------------------------

    m_neighbors [edge.m_vertex1].push_back (Neighbor (edge.m_vertex2, m_edges.size ()));
}

//--------------------------------------------------
// VECTOR PRINT

std::ostream& operator<< (std::ostream& ostream, std::vector <int> vector) {

    ostream << "printing array:\n";

    for (int i : vector) {

        ostream << i << " ";
    }

    ostream << "\n";

    //--------------------------------------------------

    return ostream;
}

