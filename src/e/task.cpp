

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

        m_bridges (),

        m_vertex_count (vertex_count),
        m_edges_count  (0),
        m_graph (),

        dfs_timer (0),
        m_enter_times            (vertex_count, -1),
        m_least_deep_accesible (vertex_count, -1)
{
    for (int i = 0; i < m_vertex_count; ++i) {

        m_graph.push_back  (Vertex_Info (i));
    }
}

//--------------------------------------------------

void Solution::add_edge (int vertex1, int vertex2) {

    m_graph [vertex1 - 1].m_neighbors.insert ({ &m_graph [vertex2 - 1], m_edges_count });
    m_graph [vertex2 - 1].m_neighbors.insert ({ &m_graph [vertex1 - 1], m_edges_count });

    //--------------------------------------------------

    ++m_edges_count;
}


void Solution::pre_solve (void) {

    
}


void Solution::solve (void) {

    for (int i = 0; i < m_vertex_count; ++i) {

        Vertex_Info& vertex = m_graph [i];
        if (vertex.m_color != WHITE) continue;

        dfs (i, -1);
    }

    //--------------------------------------------------

    std::sort (m_bridges.begin (), m_bridges.end ());
}


void Solution::print_result (void) {

    std::cout << m_bridges.size () << "\n";

    //--------------------------------------------------

    for (int i : m_bridges) {

        std::cout << i + 1 << " ";
    }

    std::cout << "\n";

    //--------------------------------------------------

    //std::cout << m_enter_times;
    //std::cout << m_least_deep_accesible;
}

//--------------------------------------------------

Neighbor_Info::Neighbor_Info (Vertex_Info* neighbor, int edge_index):

        m_neighbor   (neighbor),
        m_edge_index (edge_index) {}


bool Neighbor_Info::operator< (const Neighbor_Info& other) const {

    return m_neighbor < other.m_neighbor;
}


Vertex_Info::Vertex_Info (int number):

        m_index (number),
        m_color  (WHITE),

        m_neighbors () {}

//--------------------------------------------------

void Solution::dfs (int vertex_index, int edge_index) {

    Vertex_Info& vertex = m_graph [vertex_index];
    int& least_deep_accesible = m_least_deep_accesible [vertex_index];
    int& enter_time           = m_enter_times          [vertex_index];

    //--------------------------------------------------

    enter_time           = dfs_timer;
    least_deep_accesible = dfs_timer;
    ++dfs_timer;

    //--------------------------------------------------

    vertex.m_color = BLACK;

    for (Neighbor_Info neighbor : vertex.m_neighbors) {

        Vertex_Info& next_vertex = *neighbor.m_neighbor;

        //--------------------------------------------------

        if (neighbor.m_edge_index == edge_index) continue;

        if (next_vertex.m_color != WHITE) {

            least_deep_accesible = std::min
                    (least_deep_accesible, m_enter_times [next_vertex.m_index]);
            continue;
        }

        //--------------------------------------------------

        dfs (next_vertex.m_index, neighbor.m_edge_index);

        least_deep_accesible = std::min
                (least_deep_accesible, m_least_deep_accesible [next_vertex.m_index]);

        //--------------------------------------------------
        // не могу вернуться из ребенка

        if (m_least_deep_accesible [next_vertex.m_index] > enter_time) {

            m_bridges.push_back (neighbor.m_edge_index);
        }
    }
}


std::ostream& operator<< (std::ostream& ostream, std::vector <int> vector) {

    ostream << "printing array:\n";

    for (int i : vector) {

        ostream << i << " ";
    }

    ostream << "\n";

    //--------------------------------------------------

    return ostream;
}

