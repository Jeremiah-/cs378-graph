// --------------------------------
// projects/g++/graph/TestGraph.c++
// Copyright (C) 2015
// Glenn P. Downing
// --------------------------------

// --------
// includes
// --------

#include <iostream> // cout, endl
#include <iterator> // ostream_iterator
#include <sstream>  // ostringstream
#include <utility>  // pair

#include "boost/graph/adjacency_list.hpp"  // adjacency_list
#include "boost/graph/topological_sort.hpp"// topological_sort

#include "gtest/gtest.h"

#include "Graph.h"

using namespace std;

using testing::Test;
using testing::Types;

// ---------
// TestGraph
// ---------

template <typename G>
struct TestGraph : Test {
    // --------
    // typedefs
    // --------

    typedef          G                     graph_type;
    typedef typename G::vertex_descriptor  vertex_descriptor;
    typedef typename G::edge_descriptor    edge_descriptor;
    typedef typename G::vertex_iterator    vertex_iterator;
    typedef typename G::edge_iterator      edge_iterator;
    typedef typename G::adjacency_iterator adjacency_iterator;
    typedef typename G::vertices_size_type vertices_size_type;
    typedef typename G::edges_size_type    edges_size_type;};

// directed, sparse, unweighted
// possibly connected
// possibly cyclic
typedef Types<
            boost::adjacency_list<boost::setS, boost::vecS, boost::directedS>,
            Graph>
        graph_types;

TYPED_TEST_CASE(TestGraph, graph_types);

// ----------
// add_vertex
// ----------

TYPED_TEST(TestGraph, add_vertex1) {
    typedef typename TestFixture::graph_type         graph_type;
    typedef typename TestFixture::vertex_descriptor  vertex_descriptor;
    typedef typename TestFixture::edge_descriptor    edge_descriptor;
    typedef typename TestFixture::vertex_iterator    vertex_iterator;
    typedef typename TestFixture::edge_iterator      edge_iterator;
    typedef typename TestFixture::adjacency_iterator adjacency_iterator;
    typedef typename TestFixture::vertices_size_type vertices_size_type;
    typedef typename TestFixture::edges_size_type    edges_size_type;

    graph_type g;

    vertex_descriptor vdA = add_vertex(g);

    vertex_descriptor vd = vertex(0, g);
    ASSERT_EQ(vdA, vd);

    vertices_size_type vs = num_vertices(g);
    ASSERT_EQ(1, vs);
}

TYPED_TEST(TestGraph, add_vertex2) {
    typedef typename TestFixture::graph_type         graph_type;
    typedef typename TestFixture::vertex_descriptor  vertex_descriptor;
    typedef typename TestFixture::edge_descriptor    edge_descriptor;
    typedef typename TestFixture::vertex_iterator    vertex_iterator;
    typedef typename TestFixture::edge_iterator      edge_iterator;
    typedef typename TestFixture::adjacency_iterator adjacency_iterator;
    typedef typename TestFixture::vertices_size_type vertices_size_type;
    typedef typename TestFixture::edges_size_type    edges_size_type;

    graph_type g;

    vertex_descriptor vd1 = add_vertex(g);
    vertex_descriptor vd2 = add_vertex(g);


    ASSERT_EQ(vertex(0, g), vd1);
    ASSERT_EQ(vertex(1, g), vd2);
    ASSERT_TRUE(vertex(0, g) != vertex(1, g));

    vertices_size_type vs = num_vertices(g);
    ASSERT_EQ(2, vs);
}

TYPED_TEST(TestGraph, add_vertex3) {
    typedef typename TestFixture::graph_type         graph_type;
    typedef typename TestFixture::vertex_descriptor  vertex_descriptor;
    typedef typename TestFixture::edge_descriptor    edge_descriptor;
    typedef typename TestFixture::vertex_iterator    vertex_iterator;
    typedef typename TestFixture::edge_iterator      edge_iterator;
    typedef typename TestFixture::adjacency_iterator adjacency_iterator;
    typedef typename TestFixture::vertices_size_type vertices_size_type;
    typedef typename TestFixture::edges_size_type    edges_size_type;

    graph_type g;

    // vertex_descriptor vd1 = add_vertex(g);
    // vertex_descriptor vd2 = add_vertex(g);


    // ASSERT_EQ(vertex(0, g), vd1);
    // ASSERT_EQ(vertex(1, g), vd2);
    // ASSERT_TRUE(vertex(0, g) != vertex(1, g));

    for (int i = 0; i < 1001; ++i) {
        ASSERT_EQ(add_vertex(g), vertex(i, g));
    }

    vertices_size_type vs = num_vertices(g);
    ASSERT_EQ(1001, vs);
}


// // ----------
// // add_edge
// // ----------

TYPED_TEST(TestGraph, add_edge1) {
    typedef typename TestFixture::graph_type         graph_type;
    typedef typename TestFixture::vertex_descriptor  vertex_descriptor;
    typedef typename TestFixture::edge_descriptor    edge_descriptor;
    typedef typename TestFixture::vertex_iterator    vertex_iterator;
    typedef typename TestFixture::edge_iterator      edge_iterator;
    typedef typename TestFixture::adjacency_iterator adjacency_iterator;
    typedef typename TestFixture::vertices_size_type vertices_size_type;
    typedef typename TestFixture::edges_size_type    edges_size_type;

    graph_type g;

    vertex_descriptor vdA = add_vertex(g);
    vertex_descriptor vdB = add_vertex(g);

    edge_descriptor edAB = add_edge(vdA, vdB, g).first;
    std::cout << edAB << std::endl;
    // edge_descriptor zero = 0;
    // ASSERT_EQ(zero, edAB);

    pair<edge_descriptor, bool> p1 = add_edge(vdA, vdB, g);
    ASSERT_EQ(edAB,  p1.first);
    ASSERT_EQ(false, p1.second);

    pair<edge_descriptor, bool> p2 = edge(vdA, vdB, g);
    ASSERT_EQ(edAB, p2.first);
    ASSERT_EQ(true, p2.second);

    edges_size_type es = num_edges(g);
    ASSERT_EQ(1, es);

    vertex_descriptor vd1 = source(edAB, g);
    ASSERT_EQ(vdA, vd1);

    vertex_descriptor vd2 = target(edAB, g);
    ASSERT_EQ(vdB, vd2);
}


TYPED_TEST(TestGraph, add_edge2) {
    typedef typename TestFixture::graph_type         graph_type;
    typedef typename TestFixture::vertex_descriptor  vertex_descriptor;
    typedef typename TestFixture::edge_descriptor    edge_descriptor;
    typedef typename TestFixture::vertex_iterator    vertex_iterator;
    typedef typename TestFixture::edge_iterator      edge_iterator;
    typedef typename TestFixture::adjacency_iterator adjacency_iterator;
    typedef typename TestFixture::vertices_size_type vertices_size_type;
    typedef typename TestFixture::edges_size_type    edges_size_type;

    graph_type g;

    pair<edge_descriptor, bool> edAB = add_edge(0, 99, g);
    ASSERT_EQ(100, num_vertices(g));
    ASSERT_EQ(edge(0, 99, g).first, edAB.first);
    ASSERT_EQ(true, edAB.second);
}


TYPED_TEST(TestGraph, add_edge3) {
    typedef typename TestFixture::graph_type         graph_type;
    typedef typename TestFixture::vertex_descriptor  vertex_descriptor;
    typedef typename TestFixture::edge_descriptor    edge_descriptor;
    typedef typename TestFixture::vertex_iterator    vertex_iterator;
    typedef typename TestFixture::edge_iterator      edge_iterator;
    typedef typename TestFixture::adjacency_iterator adjacency_iterator;
    typedef typename TestFixture::vertices_size_type vertices_size_type;
    typedef typename TestFixture::edges_size_type    edges_size_type;

    graph_type g;

    add_edge(0, 999, g);
    ASSERT_EQ(1000, num_vertices(g));

    for (int i = 1; i < 999; ++i) {
        edge_descriptor e = add_edge(i, 999, g).first;
        ASSERT_EQ(edge(i, 999, g).first, e);
    }
    ASSERT_EQ(999, num_edges(g));
    ASSERT_EQ(1000, num_vertices(g));
}

TYPED_TEST(TestGraph, add_edge4) {
    typedef typename TestFixture::graph_type         graph_type;
    typedef typename TestFixture::vertex_descriptor  vertex_descriptor;
    typedef typename TestFixture::edge_descriptor    edge_descriptor;
    typedef typename TestFixture::vertex_iterator    vertex_iterator;
    typedef typename TestFixture::edge_iterator      edge_iterator;
    typedef typename TestFixture::adjacency_iterator adjacency_iterator;
    typedef typename TestFixture::vertices_size_type vertices_size_type;
    typedef typename TestFixture::edges_size_type    edges_size_type;

    graph_type g;

    add_edge(0, 999, g);
    ASSERT_EQ(1000, num_vertices(g));


    for (int i = 998; i > 0; --i) {
        edge_descriptor e = add_edge(0, i, g).first;
        ASSERT_EQ(edge(0, i, g).first, e);
    }

    ASSERT_EQ(999, num_edges(g));
    ASSERT_EQ(1000, num_vertices(g));
}


// // ----------
// // vertices
// // ----------


TYPED_TEST(TestGraph, vertices1) {
    typedef typename TestFixture::graph_type         graph_type;
    typedef typename TestFixture::vertex_descriptor  vertex_descriptor;
    typedef typename TestFixture::edge_descriptor    edge_descriptor;
    typedef typename TestFixture::vertex_iterator    vertex_iterator;
    typedef typename TestFixture::edge_iterator      edge_iterator;
    typedef typename TestFixture::adjacency_iterator adjacency_iterator;
    typedef typename TestFixture::vertices_size_type vertices_size_type;
    typedef typename TestFixture::edges_size_type    edges_size_type;

    graph_type g;

    vertex_descriptor vdA = add_vertex(g);
    vertex_descriptor vdB = add_vertex(g);

    pair<vertex_iterator, vertex_iterator> p = vertices(g);
    vertex_iterator                        b = p.first;
    vertex_iterator                        e = p.second;
    if (b != e) {
        vertex_descriptor vd = *b;
        ASSERT_EQ(vdA, vd);}
    ++b;
    if (b != e) {
        vertex_descriptor vd = *b;
        ASSERT_EQ(vdB, vd);}
    ++b;
    ASSERT_EQ(e, b);
}


TYPED_TEST(TestGraph, vertices2) {
    typedef typename TestFixture::graph_type         graph_type;
    typedef typename TestFixture::vertex_descriptor  vertex_descriptor;
    typedef typename TestFixture::edge_descriptor    edge_descriptor;
    typedef typename TestFixture::vertex_iterator    vertex_iterator;
    typedef typename TestFixture::edge_iterator      edge_iterator;
    typedef typename TestFixture::adjacency_iterator adjacency_iterator;
    typedef typename TestFixture::vertices_size_type vertices_size_type;
    typedef typename TestFixture::edges_size_type    edges_size_type;

    graph_type g;

    pair<vertex_iterator, vertex_iterator> p = vertices(g);
    ASSERT_EQ(p.first, p.second);
}


TYPED_TEST(TestGraph, vertices3) {
    typedef typename TestFixture::graph_type         graph_type;
    typedef typename TestFixture::vertex_descriptor  vertex_descriptor;
    typedef typename TestFixture::edge_descriptor    edge_descriptor;
    typedef typename TestFixture::vertex_iterator    vertex_iterator;
    typedef typename TestFixture::edge_iterator      edge_iterator;
    typedef typename TestFixture::adjacency_iterator adjacency_iterator;
    typedef typename TestFixture::vertices_size_type vertices_size_type;
    typedef typename TestFixture::edges_size_type    edges_size_type;

    graph_type g;

    for (int i = 0; i < 100; ++i) {
        add_vertex(g);
    }


    pair<vertex_iterator, vertex_iterator> p = vertices(g);
    vertex_iterator                        b = p.first;
    vertex_iterator                        e = p.second;

    for (int i = 0; i < 100; ++i) {
        ASSERT_EQ(vertex(i, g), *b);
        ++b;
    }

    ASSERT_EQ(e, b);
}


// // ----------
// // edges
// // ----------


TYPED_TEST(TestGraph, edges1) {
    typedef typename TestFixture::graph_type         graph_type;
    typedef typename TestFixture::vertex_descriptor  vertex_descriptor;
    typedef typename TestFixture::edge_descriptor    edge_descriptor;
    typedef typename TestFixture::vertex_iterator    vertex_iterator;
    typedef typename TestFixture::edge_iterator      edge_iterator;
    typedef typename TestFixture::adjacency_iterator adjacency_iterator;
    typedef typename TestFixture::vertices_size_type vertices_size_type;
    typedef typename TestFixture::edges_size_type    edges_size_type;

    graph_type g;

    vertex_descriptor vdA = add_vertex(g);
    vertex_descriptor vdB = add_vertex(g);
    vertex_descriptor vdC = add_vertex(g);

    edge_descriptor edAB = add_edge(vdA, vdB, g).first;
    edge_descriptor edAC = add_edge(vdA, vdC, g).first;

    pair<edge_iterator, edge_iterator> p = edges(g);
    edge_iterator                      b = p.first;
    edge_iterator                      e = p.second;
    if (b != e) {
        edge_descriptor ed = *b;
        ASSERT_EQ(edAB, ed);}
    ++b;
    if (b != e) {
        edge_descriptor ed = *b;
        ASSERT_EQ(edAC, ed);}
    ++b;
    ASSERT_EQ(e, b);
}


TYPED_TEST(TestGraph, edges2) {
    typedef typename TestFixture::graph_type         graph_type;
    typedef typename TestFixture::vertex_descriptor  vertex_descriptor;
    typedef typename TestFixture::edge_descriptor    edge_descriptor;
    typedef typename TestFixture::vertex_iterator    vertex_iterator;
    typedef typename TestFixture::edge_iterator      edge_iterator;
    typedef typename TestFixture::adjacency_iterator adjacency_iterator;
    typedef typename TestFixture::vertices_size_type vertices_size_type;
    typedef typename TestFixture::edges_size_type    edges_size_type;

    graph_type g;

    pair<edge_iterator, edge_iterator> p = edges(g);
    edge_iterator                      b = p.first;
    edge_iterator                      e = p.second;
    ASSERT_EQ(e, b);
}


TYPED_TEST(TestGraph, edges3) {
    typedef typename TestFixture::graph_type         graph_type;
    typedef typename TestFixture::vertex_descriptor  vertex_descriptor;
    typedef typename TestFixture::edge_descriptor    edge_descriptor;
    typedef typename TestFixture::vertex_iterator    vertex_iterator;
    typedef typename TestFixture::edge_iterator      edge_iterator;
    typedef typename TestFixture::adjacency_iterator adjacency_iterator;
    typedef typename TestFixture::vertices_size_type vertices_size_type;
    typedef typename TestFixture::edges_size_type    edges_size_type;

    graph_type g;

    add_edge(0, 99, g);

    for (int i = 1; i < 99; ++i) {
        add_edge(i, 99, g);
        add_edge(0, i, g);
    }

    ASSERT_EQ(197, num_edges(g));

    pair<edge_iterator, edge_iterator> p = edges(g);
    edge_iterator                      b = p.first;
    edge_iterator                      e = p.second;


    // this is wrong. The edges are sorted by smallest vertex to largest
    // ASSERT_EQ(edge(0, 99, g).first, *b);
    // ++b;

    // for (int i = 1; i < 99; ++i) {
    //     ASSERT_EQ(edge(i, 99, g).first, *b);
    //     ++b;
    //     ASSERT_EQ(edge(0, i, g).first, *b);
    //     ++b;
    // }

    ASSERT_EQ(edge(0, 1, g).first, *b);
    ++b;

    for (int i = 2; i < 99; ++i) {
        ASSERT_EQ(edge(0, i, g).first, *b);
        ++b;
    }

    for (int i = 0; i < 99; ++i) {
        ASSERT_EQ(edge(i, 99, g).first, *b);
        ++b;
    }
    ASSERT_EQ(e, b);
}



// // ----------
// // adjacent_vertices
// // ----------


TYPED_TEST(TestGraph, adjacent_vertices1) {
    typedef typename TestFixture::graph_type         graph_type;
    typedef typename TestFixture::vertex_descriptor  vertex_descriptor;
    typedef typename TestFixture::edge_descriptor    edge_descriptor;
    typedef typename TestFixture::vertex_iterator    vertex_iterator;
    typedef typename TestFixture::edge_iterator      edge_iterator;
    typedef typename TestFixture::adjacency_iterator adjacency_iterator;
    typedef typename TestFixture::vertices_size_type vertices_size_type;
    typedef typename TestFixture::edges_size_type    edges_size_type;

    graph_type g;

    vertex_descriptor vdA = add_vertex(g);
    vertex_descriptor vdB = add_vertex(g);
    vertex_descriptor vdC = add_vertex(g);

    add_edge(vdA, vdB, g);
    add_edge(vdA, vdC, g);

    pair<adjacency_iterator, adjacency_iterator> p = adjacent_vertices(vdA, g);
    adjacency_iterator                           b = p.first;
    adjacency_iterator                           e = p.second;
    if (b != e) {
        vertex_descriptor vd = *b;
        ASSERT_EQ(vdB, vd);}
    ++b;
    if (b != e) {
        vertex_descriptor vd = *b;
        ASSERT_EQ(vdC, vd);}
    ++b;
    ASSERT_EQ(e, b);
}

TYPED_TEST(TestGraph, adjacent_vertices2) {
    typedef typename TestFixture::graph_type         graph_type;
    typedef typename TestFixture::vertex_descriptor  vertex_descriptor;
    typedef typename TestFixture::edge_descriptor    edge_descriptor;
    typedef typename TestFixture::vertex_iterator    vertex_iterator;
    typedef typename TestFixture::edge_iterator      edge_iterator;
    typedef typename TestFixture::adjacency_iterator adjacency_iterator;
    typedef typename TestFixture::vertices_size_type vertices_size_type;
    typedef typename TestFixture::edges_size_type    edges_size_type;

    graph_type g;

    vertex_descriptor vdA = add_vertex(g);
    vertex_descriptor vdB = add_vertex(g);
    vertex_descriptor vdC = add_vertex(g);

    add_edge(vdA, vdB, g);
    add_edge(vdA, vdC, g);

    pair<adjacency_iterator, adjacency_iterator> p = adjacent_vertices(vdC, g);
    adjacency_iterator                           b = p.first;
    adjacency_iterator                           e = p.second;
    ASSERT_EQ(e, b);
}


TYPED_TEST(TestGraph, adjacent_vertices3) {
    typedef typename TestFixture::graph_type         graph_type;
    typedef typename TestFixture::vertex_descriptor  vertex_descriptor;
    typedef typename TestFixture::edge_descriptor    edge_descriptor;
    typedef typename TestFixture::vertex_iterator    vertex_iterator;
    typedef typename TestFixture::edge_iterator      edge_iterator;
    typedef typename TestFixture::adjacency_iterator adjacency_iterator;
    typedef typename TestFixture::vertices_size_type vertices_size_type;
    typedef typename TestFixture::edges_size_type    edges_size_type;

    graph_type g;

    add_edge(0, 99, g);

    for (int i = 98; i > 0; --i) {
        add_edge(0, i, g);
    }

    pair<adjacency_iterator, adjacency_iterator> p = adjacent_vertices(0, g);
    adjacency_iterator                           b = p.first;
    adjacency_iterator                           e = p.second;

    for (int i = 1; i < 100; ++i) {
        ASSERT_EQ(vertex(i, g), *b);  
        ++b;
    }
    ASSERT_EQ(e, b);
}


// // ----------
// // edge
// // ----------


TYPED_TEST(TestGraph, edge1) {
    typedef typename TestFixture::graph_type         graph_type;
    typedef typename TestFixture::vertex_descriptor  vertex_descriptor;
    typedef typename TestFixture::edge_descriptor    edge_descriptor;
    typedef typename TestFixture::vertex_iterator    vertex_iterator;
    typedef typename TestFixture::edge_iterator      edge_iterator;
    typedef typename TestFixture::adjacency_iterator adjacency_iterator;
    typedef typename TestFixture::vertices_size_type vertices_size_type;
    typedef typename TestFixture::edges_size_type    edges_size_type;

    graph_type g;

    vertex_descriptor vdA = add_vertex(g);
    vertex_descriptor vdB = add_vertex(g);
    vertex_descriptor vdC = add_vertex(g);

    edge_descriptor x = add_edge(vdA, vdB, g).first;
    edge_descriptor y = add_edge(vdA, vdC, g).first;

    pair<edge_descriptor, bool> p = edge(vdA, vdB, g);
    edge_descriptor e = p.first;
    bool b = p.second;


    ASSERT_TRUE(b);
    ASSERT_EQ(x, e);
}

TYPED_TEST(TestGraph, edge2) {
    typedef typename TestFixture::graph_type         graph_type;
    typedef typename TestFixture::vertex_descriptor  vertex_descriptor;
    typedef typename TestFixture::edge_descriptor    edge_descriptor;
    typedef typename TestFixture::vertex_iterator    vertex_iterator;
    typedef typename TestFixture::edge_iterator      edge_iterator;
    typedef typename TestFixture::adjacency_iterator adjacency_iterator;
    typedef typename TestFixture::vertices_size_type vertices_size_type;
    typedef typename TestFixture::edges_size_type    edges_size_type;

    graph_type g;

    vertex_descriptor vdA = add_vertex(g);
    vertex_descriptor vdB = add_vertex(g);
    vertex_descriptor vdC = add_vertex(g);

    edge_descriptor x = add_edge(vdA, vdB, g).first;
    edge_descriptor y = add_edge(vdA, vdC, g).first;

    pair<edge_descriptor, bool> p = edge(vdA, vdC, g);
    edge_descriptor e = p.first;
    bool b = p.second;


    ASSERT_TRUE(b);
    ASSERT_EQ(y, e);
}

TYPED_TEST(TestGraph, edge3) {
    typedef typename TestFixture::graph_type         graph_type;
    typedef typename TestFixture::vertex_descriptor  vertex_descriptor;
    typedef typename TestFixture::edge_descriptor    edge_descriptor;
    typedef typename TestFixture::vertex_iterator    vertex_iterator;
    typedef typename TestFixture::edge_iterator      edge_iterator;
    typedef typename TestFixture::adjacency_iterator adjacency_iterator;
    typedef typename TestFixture::vertices_size_type vertices_size_type;
    typedef typename TestFixture::edges_size_type    edges_size_type;

    graph_type g;

    vertex_descriptor vdA = add_vertex(g);
    vertex_descriptor vdB = add_vertex(g);
    vertex_descriptor vdC = add_vertex(g);

    edge_descriptor x = add_edge(vdA, vdB, g).first;
    edge_descriptor y = add_edge(vdA, vdC, g).first;

    pair<edge_descriptor, bool> p = edge(vdC, vdA, g);
    edge_descriptor e = p.first;
    bool b = p.second;


    ASSERT_FALSE(b);
    // ASSERT_EQ(y, e);
}

TYPED_TEST(TestGraph, edge4) {
    typedef typename TestFixture::graph_type         graph_type;
    typedef typename TestFixture::vertex_descriptor  vertex_descriptor;
    typedef typename TestFixture::edge_descriptor    edge_descriptor;
    typedef typename TestFixture::vertex_iterator    vertex_iterator;
    typedef typename TestFixture::edge_iterator      edge_iterator;
    typedef typename TestFixture::adjacency_iterator adjacency_iterator;
    typedef typename TestFixture::vertices_size_type vertices_size_type;
    typedef typename TestFixture::edges_size_type    edges_size_type;

    graph_type g;

    vertex_descriptor vdA = add_vertex(g);
    vertex_descriptor vdB = add_vertex(g);
    vertex_descriptor vdC = add_vertex(g);

    edge_descriptor x = add_edge(vdA, vdB, g).first;
    edge_descriptor y = add_edge(vdA, vdC, g).first;

    pair<edge_descriptor, bool> p = edge(vdB, vdA, g);
    edge_descriptor e = p.first;
    bool b = p.second;


    ASSERT_FALSE(b);
    // ASSERT_EQ(y, e);
}

TYPED_TEST(TestGraph, edge5) {
    typedef typename TestFixture::graph_type         graph_type;
    typedef typename TestFixture::vertex_descriptor  vertex_descriptor;
    typedef typename TestFixture::edge_descriptor    edge_descriptor;
    typedef typename TestFixture::vertex_iterator    vertex_iterator;
    typedef typename TestFixture::edge_iterator      edge_iterator;
    typedef typename TestFixture::adjacency_iterator adjacency_iterator;
    typedef typename TestFixture::vertices_size_type vertices_size_type;
    typedef typename TestFixture::edges_size_type    edges_size_type;

    graph_type g;

    vertex_descriptor vdA = add_vertex(g);
    vertex_descriptor vdB = add_vertex(g);
    vertex_descriptor vdC = add_vertex(g);

    edge_descriptor x = add_edge(vdA, vdB, g).first;
    edge_descriptor y = add_edge(vdA, vdC, g).first;

    pair<edge_descriptor, bool> p = edge(vdB, vdC, g);
    edge_descriptor e = p.first;
    bool b = p.second;


    ASSERT_FALSE(b);
    // ASSERT_EQ(y, e);
}


// // breaks the regular adjacency list
// TYPED_TEST(TestGraph, edge6) {
//     typedef typename TestFixture::graph_type         graph_type;
//     typedef typename TestFixture::vertex_descriptor  vertex_descriptor;
//     typedef typename TestFixture::edge_descriptor    edge_descriptor;
//     typedef typename TestFixture::vertex_iterator    vertex_iterator;
//     typedef typename TestFixture::edge_iterator      edge_iterator;
//     typedef typename TestFixture::adjacency_iterator adjacency_iterator;
//     typedef typename TestFixture::vertices_size_type vertices_size_type;
//     typedef typename TestFixture::edges_size_type    edges_size_type;

//     graph_type g;

//     // vertex_descriptor vdA = add_vertex(g);
//     // vertex_descriptor vdB = add_vertex(g);
//     // vertex_descriptor vdC = add_vertex(g);

//     // edge_descriptor x = add_edge(vdA, vdB, g).first;
//     // edge_descriptor y = add_edge(vdA, vdC, g).first;

//     pair<edge_descriptor, bool> p = edge(1, 0, g);
//     edge_descriptor e = p.first;
//     bool b = p.second;


//     ASSERT_FALSE(b);
//     // ASSERT_EQ(y, e);
// }


// // ----------
// // num_edges
// // ----------

TYPED_TEST(TestGraph, num_edges1) {
    typedef typename TestFixture::graph_type         graph_type;
    typedef typename TestFixture::vertex_descriptor  vertex_descriptor;
    typedef typename TestFixture::edge_descriptor    edge_descriptor;
    typedef typename TestFixture::vertex_iterator    vertex_iterator;
    typedef typename TestFixture::edge_iterator      edge_iterator;
    typedef typename TestFixture::adjacency_iterator adjacency_iterator;
    typedef typename TestFixture::vertices_size_type vertices_size_type;
    typedef typename TestFixture::edges_size_type    edges_size_type;

    graph_type g;


    ASSERT_EQ(0, num_edges(g));
    // ASSERT_EQ(y, e);
}

TYPED_TEST(TestGraph, num_edges2) {
    typedef typename TestFixture::graph_type         graph_type;
    typedef typename TestFixture::vertex_descriptor  vertex_descriptor;
    typedef typename TestFixture::edge_descriptor    edge_descriptor;
    typedef typename TestFixture::vertex_iterator    vertex_iterator;
    typedef typename TestFixture::edge_iterator      edge_iterator;
    typedef typename TestFixture::adjacency_iterator adjacency_iterator;
    typedef typename TestFixture::vertices_size_type vertices_size_type;
    typedef typename TestFixture::edges_size_type    edges_size_type;

    graph_type g;

    vertex_descriptor vdA = add_vertex(g);
    vertex_descriptor vdB = add_vertex(g);
    vertex_descriptor vdC = add_vertex(g);


    ASSERT_EQ(0, num_edges(g));
    // ASSERT_EQ(y, e);
}

TYPED_TEST(TestGraph, num_edges3) {
    typedef typename TestFixture::graph_type         graph_type;
    typedef typename TestFixture::vertex_descriptor  vertex_descriptor;
    typedef typename TestFixture::edge_descriptor    edge_descriptor;
    typedef typename TestFixture::vertex_iterator    vertex_iterator;
    typedef typename TestFixture::edge_iterator      edge_iterator;
    typedef typename TestFixture::adjacency_iterator adjacency_iterator;
    typedef typename TestFixture::vertices_size_type vertices_size_type;
    typedef typename TestFixture::edges_size_type    edges_size_type;

    graph_type g;

    vertex_descriptor vdA = add_vertex(g);
    vertex_descriptor vdB = add_vertex(g);
    vertex_descriptor vdC = add_vertex(g);

    edge_descriptor x = add_edge(vdA, vdB, g).first;
    edge_descriptor y = add_edge(vdA, vdC, g).first;
    add_edge(vdA, vdC, g);

    ASSERT_EQ(2, num_edges(g));
    // ASSERT_EQ(y, e);
}

TYPED_TEST(TestGraph, num_edges4) {
    typedef typename TestFixture::graph_type         graph_type;
    typedef typename TestFixture::vertex_descriptor  vertex_descriptor;
    typedef typename TestFixture::edge_descriptor    edge_descriptor;
    typedef typename TestFixture::vertex_iterator    vertex_iterator;
    typedef typename TestFixture::edge_iterator      edge_iterator;
    typedef typename TestFixture::adjacency_iterator adjacency_iterator;
    typedef typename TestFixture::vertices_size_type vertices_size_type;
    typedef typename TestFixture::edges_size_type    edges_size_type;

    graph_type g;

    for (int i = 1; i < 99; ++i) {
        add_edge(i, 99, g);
        add_edge(0, i, g);
    }

    ASSERT_EQ(196, num_edges(g));
    // ASSERT_EQ(y, e);
}


// ----------
// num_vertices
// ----------

TYPED_TEST(TestGraph, num_vertices1) {
    typedef typename TestFixture::graph_type         graph_type;
    typedef typename TestFixture::vertex_descriptor  vertex_descriptor;
    typedef typename TestFixture::edge_descriptor    edge_descriptor;
    typedef typename TestFixture::vertex_iterator    vertex_iterator;
    typedef typename TestFixture::edge_iterator      edge_iterator;
    typedef typename TestFixture::adjacency_iterator adjacency_iterator;
    typedef typename TestFixture::vertices_size_type vertices_size_type;
    typedef typename TestFixture::edges_size_type    edges_size_type;

    graph_type g;


    ASSERT_EQ(0, num_vertices(g));
    // ASSERT_EQ(y, e);
}

TYPED_TEST(TestGraph, num_vertices2) {
    typedef typename TestFixture::graph_type         graph_type;
    typedef typename TestFixture::vertex_descriptor  vertex_descriptor;
    typedef typename TestFixture::edge_descriptor    edge_descriptor;
    typedef typename TestFixture::vertex_iterator    vertex_iterator;
    typedef typename TestFixture::edge_iterator      edge_iterator;
    typedef typename TestFixture::adjacency_iterator adjacency_iterator;
    typedef typename TestFixture::vertices_size_type vertices_size_type;
    typedef typename TestFixture::edges_size_type    edges_size_type;

    graph_type g;
    add_vertex(g);


    ASSERT_EQ(1, num_vertices(g));
    // ASSERT_EQ(y, e);
}

TYPED_TEST(TestGraph, num_vertices3) {
    typedef typename TestFixture::graph_type         graph_type;
    typedef typename TestFixture::vertex_descriptor  vertex_descriptor;
    typedef typename TestFixture::edge_descriptor    edge_descriptor;
    typedef typename TestFixture::vertex_iterator    vertex_iterator;
    typedef typename TestFixture::edge_iterator      edge_iterator;
    typedef typename TestFixture::adjacency_iterator adjacency_iterator;
    typedef typename TestFixture::vertices_size_type vertices_size_type;
    typedef typename TestFixture::edges_size_type    edges_size_type;

    graph_type g;
    
    add_edge(0, 99, g);

    ASSERT_EQ(100, num_vertices(g));
    // ASSERT_EQ(y, e);
}

// ----------
// source
// ----------

TYPED_TEST(TestGraph, source1) {
    typedef typename TestFixture::graph_type         graph_type;
    typedef typename TestFixture::vertex_descriptor  vertex_descriptor;
    typedef typename TestFixture::edge_descriptor    edge_descriptor;
    typedef typename TestFixture::vertex_iterator    vertex_iterator;
    typedef typename TestFixture::edge_iterator      edge_iterator;
    typedef typename TestFixture::adjacency_iterator adjacency_iterator;
    typedef typename TestFixture::vertices_size_type vertices_size_type;
    typedef typename TestFixture::edges_size_type    edges_size_type;

    graph_type g;
    
    edge_descriptor e = add_edge(0, 99, g).first;
    vertex_descriptor x = 0;

    ASSERT_EQ(x, source(e, g));
}

TYPED_TEST(TestGraph, source2) {
    typedef typename TestFixture::graph_type         graph_type;
    typedef typename TestFixture::vertex_descriptor  vertex_descriptor;
    typedef typename TestFixture::edge_descriptor    edge_descriptor;
    typedef typename TestFixture::vertex_iterator    vertex_iterator;
    typedef typename TestFixture::edge_iterator      edge_iterator;
    typedef typename TestFixture::adjacency_iterator adjacency_iterator;
    typedef typename TestFixture::vertices_size_type vertices_size_type;
    typedef typename TestFixture::edges_size_type    edges_size_type;

    graph_type g;
    
    edge_descriptor e = add_edge(0, 99, g).first;
    vertex_descriptor x = 99;

    ASSERT_TRUE(x != source(e, g));
}

TYPED_TEST(TestGraph, source3) {
    typedef typename TestFixture::graph_type         graph_type;
    typedef typename TestFixture::vertex_descriptor  vertex_descriptor;
    typedef typename TestFixture::edge_descriptor    edge_descriptor;
    typedef typename TestFixture::vertex_iterator    vertex_iterator;
    typedef typename TestFixture::edge_iterator      edge_iterator;
    typedef typename TestFixture::adjacency_iterator adjacency_iterator;
    typedef typename TestFixture::vertices_size_type vertices_size_type;
    typedef typename TestFixture::edges_size_type    edges_size_type;

    graph_type g;
    graph_type temp;
    edge_descriptor x = add_edge(99, 8, temp).first;
    
    // edge_descriptor e = add_edge(0, 99, g).first;
    vertex_descriptor v = 99;

    ASSERT_EQ(v, source(x, g));
}

TYPED_TEST(TestGraph, source4) {
    typedef typename TestFixture::graph_type         graph_type;
    typedef typename TestFixture::vertex_descriptor  vertex_descriptor;
    typedef typename TestFixture::edge_descriptor    edge_descriptor;
    typedef typename TestFixture::vertex_iterator    vertex_iterator;
    typedef typename TestFixture::edge_iterator      edge_iterator;
    typedef typename TestFixture::adjacency_iterator adjacency_iterator;
    typedef typename TestFixture::vertices_size_type vertices_size_type;
    typedef typename TestFixture::edges_size_type    edges_size_type;

    graph_type g;
    
    edge_descriptor e = add_edge(0, 99, g).first;
    vertex_descriptor x = 0;

    ASSERT_EQ(x, source(e, g));
}

TYPED_TEST(TestGraph, source5) {
    typedef typename TestFixture::graph_type         graph_type;
    typedef typename TestFixture::vertex_descriptor  vertex_descriptor;
    typedef typename TestFixture::edge_descriptor    edge_descriptor;
    typedef typename TestFixture::vertex_iterator    vertex_iterator;
    typedef typename TestFixture::edge_iterator      edge_iterator;
    typedef typename TestFixture::adjacency_iterator adjacency_iterator;
    typedef typename TestFixture::vertices_size_type vertices_size_type;
    typedef typename TestFixture::edges_size_type    edges_size_type;

    graph_type g;
    
    edge_descriptor e = add_edge(0, 99, g).first;
    vertex_descriptor x = 99;

    ASSERT_TRUE(x != source(e, g));
}

TYPED_TEST(TestGraph, source6) {
    typedef typename TestFixture::graph_type         graph_type;
    typedef typename TestFixture::vertex_descriptor  vertex_descriptor;
    typedef typename TestFixture::edge_descriptor    edge_descriptor;
    typedef typename TestFixture::vertex_iterator    vertex_iterator;
    typedef typename TestFixture::edge_iterator      edge_iterator;
    typedef typename TestFixture::adjacency_iterator adjacency_iterator;
    typedef typename TestFixture::vertices_size_type vertices_size_type;
    typedef typename TestFixture::edges_size_type    edges_size_type;

    graph_type g;
    graph_type temp;
    edge_descriptor x = add_edge(99, 8, temp).first;
    
    // edge_descriptor e = add_edge(0, 99, g).first;
    vertex_descriptor v = 99;

    ASSERT_EQ(v, source(x, g));
}

// ----------
// target
// ----------

TYPED_TEST(TestGraph, target1) {
    typedef typename TestFixture::graph_type         graph_type;
    typedef typename TestFixture::vertex_descriptor  vertex_descriptor;
    typedef typename TestFixture::edge_descriptor    edge_descriptor;
    typedef typename TestFixture::vertex_iterator    vertex_iterator;
    typedef typename TestFixture::edge_iterator      edge_iterator;
    typedef typename TestFixture::adjacency_iterator adjacency_iterator;
    typedef typename TestFixture::vertices_size_type vertices_size_type;
    typedef typename TestFixture::edges_size_type    edges_size_type;

    graph_type g;
    
    edge_descriptor e = add_edge(0, 99, g).first;
    vertex_descriptor x = 99;

    ASSERT_EQ(x, target(e, g));
}

TYPED_TEST(TestGraph, target2) {
    typedef typename TestFixture::graph_type         graph_type;
    typedef typename TestFixture::vertex_descriptor  vertex_descriptor;
    typedef typename TestFixture::edge_descriptor    edge_descriptor;
    typedef typename TestFixture::vertex_iterator    vertex_iterator;
    typedef typename TestFixture::edge_iterator      edge_iterator;
    typedef typename TestFixture::adjacency_iterator adjacency_iterator;
    typedef typename TestFixture::vertices_size_type vertices_size_type;
    typedef typename TestFixture::edges_size_type    edges_size_type;

    graph_type g;
    
    edge_descriptor e = add_edge(0, 99, g).first;
    vertex_descriptor x = 0;

    ASSERT_TRUE(x != target(e, g));
}

TYPED_TEST(TestGraph, target3) {
    typedef typename TestFixture::graph_type         graph_type;
    typedef typename TestFixture::vertex_descriptor  vertex_descriptor;
    typedef typename TestFixture::edge_descriptor    edge_descriptor;
    typedef typename TestFixture::vertex_iterator    vertex_iterator;
    typedef typename TestFixture::edge_iterator      edge_iterator;
    typedef typename TestFixture::adjacency_iterator adjacency_iterator;
    typedef typename TestFixture::vertices_size_type vertices_size_type;
    typedef typename TestFixture::edges_size_type    edges_size_type;

    graph_type g;
    graph_type temp;
    edge_descriptor x = add_edge(99, 8, temp).first;
    
    // edge_descriptor e = add_edge(0, 99, g).first;
    vertex_descriptor v = 8;

    ASSERT_EQ(v, target(x, g));
}

// ----------
// vertex
// ----------

TYPED_TEST(TestGraph, vertex1) {
    typedef typename TestFixture::graph_type         graph_type;
    typedef typename TestFixture::vertex_descriptor  vertex_descriptor;
    typedef typename TestFixture::edge_descriptor    edge_descriptor;
    typedef typename TestFixture::vertex_iterator    vertex_iterator;
    typedef typename TestFixture::edge_iterator      edge_iterator;
    typedef typename TestFixture::adjacency_iterator adjacency_iterator;
    typedef typename TestFixture::vertices_size_type vertices_size_type;
    typedef typename TestFixture::edges_size_type    edges_size_type;

    graph_type g;
    
    edge_descriptor e = add_edge(0, 99, g).first;
    vertex_descriptor x = 4;

    ASSERT_EQ(x, vertex(4, g));
}

TYPED_TEST(TestGraph, vertex2) {
    typedef typename TestFixture::graph_type         graph_type;
    typedef typename TestFixture::vertex_descriptor  vertex_descriptor;
    typedef typename TestFixture::edge_descriptor    edge_descriptor;
    typedef typename TestFixture::vertex_iterator    vertex_iterator;
    typedef typename TestFixture::edge_iterator      edge_iterator;
    typedef typename TestFixture::adjacency_iterator adjacency_iterator;
    typedef typename TestFixture::vertices_size_type vertices_size_type;
    typedef typename TestFixture::edges_size_type    edges_size_type;

    graph_type g;
    
    edge_descriptor e = add_edge(0, 99, g).first;
    vertex_descriptor x = 200;

    // returns the num given
    ASSERT_EQ(x, vertex(200, g));
}