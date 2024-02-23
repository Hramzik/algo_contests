
//--------------------------------------------------

#include <iostream>
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
        graph.add_edge (vertex1, vertex2, 0);
    }

    //--------------------------------------------------

    KSSFinder finder (graph);
    std::vector <int> answer = finder.solve ();

    //--------------------------------------------------

    int kss_count = answer [answer.size () - 1];
    std::cout << kss_count << "\n";

    //--------------------------------------------------

    for (int i : answer) {

        std::cout << kss_count - i << " ";
    }

    //--------------------------------------------------

    return 0;
}


//--------------------------------------------------

KSSFinder::KSSFinder (const Graph& graph):

        m_kss_indexes (graph.m_vertex_count, -1),
        current_kss (0),

        m_graph  (graph),
        m_rgraph (graph.get_rgraph ()),

        m_graph_dfs_colors  (graph.m_vertex_count),
        m_rgraph_dfs_colors (graph.m_vertex_count),

        reordered_vertexes () {}

//--------------------------------------------------

std::vector <int> KSSFinder::solve (void) {

    for (int i = 0; i < m_graph.m_vertex_count; ++i) {

        if (m_graph_dfs_colors [i] != WHITE) continue;

        //--------------------------------------------------

        rgraph_dfs (i);
    }

    std::reverse (reordered_vertexes.begin (), reordered_vertexes.end ());

    //--------------------------------------------------

    for (int i : reordered_vertexes) {

        if (m_graph_dfs_colors [i] != WHITE) continue;

        //--------------------------------------------------

        dfs (i);
        ++current_kss;
    }

    //--------------------------------------------------

    m_kss_indexes.push_back (current_kss);

    return m_kss_indexes;
}

//--------------------------------------------------

void KSSFinder::dfs (int vertex_index) {

    m_graph_dfs_colors [vertex_index] = BLACK;

    //--------------------------------------------------

    m_kss_indexes [vertex_index] = current_kss;

    for (Neighbor neighbor : m_graph.m_neighbors [vertex_index]) {

        if (m_graph_dfs_colors [neighbor.m_vertex] != WHITE) continue;
        dfs (neighbor.m_vertex);
    }
}

void KSSFinder::rgraph_dfs (int vertex_index) {

    m_rgraph_dfs_colors [vertex_index] = BLACK;

    //--------------------------------------------------

    for (Neighbor neighbor : m_rgraph.m_neighbors [vertex_index]) {

        if (m_rgraph_dfs_colors [neighbor.m_vertex] != WHITE) continue;
        rgraph_dfs (neighbor.m_vertex);
    }

    //--------------------------------------------------

    reordered_vertexes.push_back (vertex_index);
}

//--------------------------------------------------
// GRAPH CODE

Edge::Edge (int vertex1, int vertex2, int weight):
        m_vertex1 (vertex1),
        m_vertex2 (vertex2),
        m_weight  (weight) {}

//--------------------------------------------------

Neighbor::Neighbor (int vertex, int weight):
        m_vertex (vertex),
        m_weight (weight) {}

//--------------------------------------------------

Graph::Graph (int vertex_count):

        m_vertex_count (vertex_count),
        m_edges (),
        m_neighbors (vertex_count) {}

void Graph::add_adge (Edge edge) {

    m_edges.push_back (edge);

    //--------------------------------------------------

    m_neighbors [edge.m_vertex1].push_back (Neighbor (edge.m_vertex2, edge.m_weight));
}

Graph Graph::get_rgraph (void) {

    Graph rgraph (m_vertex_count);

    //--------------------------------------------------

    for (Edge e : m_edges) {

        rgraph.add_adge (Edge (e.m_vertex2, e.m_vertex1, e.m_weight));
    }

    //--------------------------------------------------

    return rgraph;
}

//--------------------------------------------------

