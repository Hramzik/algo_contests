
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

    Solution solution (vertex_count);

    //--------------------------------------------------

    int edges_count  = 0;
    std::cin >> edges_count;

    int vertex1 = 0;
    int vertex2 = 0;

    for (int i = 0; i < edges_count; ++i) {

        std::cin >> vertex1 >> vertex2;
        solution.add_edge (vertex1, vertex2);
    }

    //--------------------------------------------------

    solution.pre_solve ();
    solution.solve ();
    solution.print_result ();


    return 0;
}


//--------------------------------------------------

Solution::Solution (int vertex_count):

        m_kss_indexes (vertex_count, -1),
        current_kss (0),

        m_vertex_count (vertex_count),
        m_graph (),
        m_rgraph (),
        reordered_vertexes ()
{
    for (int i = 0; i < m_vertex_count; ++i) {

        m_graph.push_back  (Vertex_Info (i));
        m_rgraph.push_back (Vertex_Info (i));
    }
}

//--------------------------------------------------

void Solution::add_edge (int vertex1, int vertex2) {

    m_graph  [vertex1 - 1].m_neighbors.insert (&m_graph  [vertex2 - 1]);
    m_rgraph [vertex2 - 1].m_neighbors.insert (&m_rgraph [vertex1 - 1]);
}


void Solution::pre_solve (void) {

    
}


void Solution::solve (void) {

    for (int i = 0; i < m_vertex_count; ++i) {

        Vertex_Info& vertex = m_rgraph [i];
        if (vertex.m_color != WHITE) continue;

        //--------------------------------------------------

        rgraph_dfs (i);
    }

    std::reverse (reordered_vertexes.begin (), reordered_vertexes.end ());

    //--------------------------------------------------

    for (int i : reordered_vertexes) {

        Vertex_Info& vertex = m_graph [i];
        if (vertex.m_color != WHITE) continue;

        //--------------------------------------------------

        dfs (i);
        ++current_kss;
    }
}


void Solution::print_result (void) {

    std::cout << current_kss << "\n";

    //--------------------------------------------------

    for (int i : m_kss_indexes) {

        std::cout << current_kss - i << " ";
    }
}

//--------------------------------------------------

Vertex_Info::Vertex_Info (int number):

        m_index (number),
        m_color  (WHITE),

        m_neighbors () {}

//--------------------------------------------------

void Solution::dfs (int vertex_index) {

    Vertex_Info& vertex = m_graph [vertex_index];

    //--------------------------------------------------

    vertex.m_color = BLACK;
    m_kss_indexes [vertex_index] = current_kss;

    for (Vertex_Info* next_vertex : vertex.m_neighbors) {

        if (next_vertex->m_color != WHITE) continue;
        dfs (next_vertex->m_index);
    }
}


void Solution::rgraph_dfs (int vertex_index) {

    Vertex_Info& vertex = m_rgraph [vertex_index];

    //--------------------------------------------------

    vertex.m_color = BLACK;

    for (Vertex_Info* next_vertex : vertex.m_neighbors) {

        if (next_vertex->m_color != WHITE) continue;
        rgraph_dfs (next_vertex->m_index);
    }

    //--------------------------------------------------

    reordered_vertexes.push_back (vertex_index);
}

