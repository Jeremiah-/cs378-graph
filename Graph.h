// --------------------------
// projects/c++/graph/Graph.h
// Copyright (C) 2015
// Glenn P. Downing
// --------------------------

#ifndef Graph_h
#define Graph_h

// --------
// includes
// --------

#include <cassert> // assert
#include <cstddef> // size_t
#include <utility> // make_pair, pair
#include <vector>  // vector

// -----
// Graph
// -----

class Graph {
    public:
        // --------
        // typedefs
        // --------

        typedef int vertex_descriptor;  // fix!
        typedef std::pair<vertex_descriptor, vertex_descriptor> edge_descriptor;    // fix!

        typedef vertex_descriptor* vertex_iterator;    // fix!
        typedef edge_descriptor* edge_iterator;      // fix!
        typedef vertex_descriptor* adjacency_iterator; // fix!

        typedef std::size_t vertices_size_type;
        typedef std::size_t edges_size_type;

    public:
        // --------
        // add_edge
        // --------

        /**
         * Adds a directed edge from source to edge.
         * Returns a pair, the edge descriptor and a boolean.
         * true if the add was successful, false if not.
         * Will return false if the edge already exists from source and dest, the existing edge_descriptor is returned
         * Does not allow edges where source == dest.
         * If source or dest > vertices(), the new size will be max(source, dest) + 1
            and new vertices will be created to fill the new size.
         *
         */
        friend std::pair<edge_descriptor, bool> add_edge (vertex_descriptor source, vertex_descriptor dest, Graph& graph) {
            // <your code>
            edge_descriptor ed = std::make_pair(source, dest);

            // this is not allowed
            if (source == dest) {
                return std::make_pair(ed, false);
            }

            // increase the size of the graph if source or dest is out of range
            if (source > (num_vertices(graph) - 1) || dest > (num_vertices(graph) - 1)) {
                for (vertices_size_type i = num_vertices(graph); i <= std::max(source, dest); ++i) {
                    add_vertex(graph);
                }
            }
            
            // if empty, add this edge
            if (graph.edge_list.empty()) {
                graph.edge_list.insert(ed);
                graph.g[source].insert(dest);
                return std::make_pair(ed, true);

            } else {
                // if the element is not found, we can insert it
                if (graph.g[source].find(dest) == graph.g[source].end()) {
                    graph.edge_list.insert(ed);
                    graph.g[source].insert(dest);
                    return std::make_pair(ed, true);

                } else { // else it is already in there
                    return std::make_pair(ed, false);
                }
            }
        }

            

        // ----------
        // add_vertex
        // ----------

        /**
         * Adds a vertex to the graph and returns the vertex descriptor for the new vertex.
         */
        friend vertex_descriptor add_vertex (Graph& graph) {
            // <your code>
            vertex_descriptor v = num_vertices(graph); // fix
            graph.g.push_back(std::set<vertex_descriptor>());

            assert(graph.g.size() == (v + 1));
            assert(graph.g[v].empty());

            return v;}

        // -----------------
        // adjacent_vertices
        // -----------------

        /**
         * Returns iterators that travel over vertices that v points to
         */
        friend std::pair<adjacency_iterator, adjacency_iterator> adjacent_vertices (vertex_descriptor v, const Graph& graph) {
            // <your code>
            vertex_descriptor a [] = {0, 0};     // dummy data
            adjacency_iterator b = a;
            adjacency_iterator e = a + 2;
            return std::make_pair(b, e);}

        // ----
        // edge
        // ----

        /**
         * returns the edge_descriptor of the edge pointing from source to target
         * if the edge does not exist, returns false and an arbitrary edge number
         */
        friend std::pair<edge_descriptor, bool> edge (vertex_descriptor source, vertex_descriptor dest, const Graph& graph) {
            // <your code>
            edge_descriptor ed = std::make_pair(0, 1);
            bool            b  = true;
            return std::make_pair(ed, b);}

        // -----
        // edges
        // -----

        /**
         * returns iterator that travel over all the edges in the graph.
         * starts from the first indexed vertex with an edge. 
         */
        friend std::pair<edge_iterator, edge_iterator> edges (const Graph& graph) {
            // <your code>
            edge_descriptor a [] = {std::make_pair(0, 1)};     // dummy data
            edge_iterator b = a;
            edge_iterator e = a + 1;
            return std::make_pair(b, e);}

        // ---------
        // num_edges
        // ---------

        /**
         * returns the number of edges in the graph
         */
        friend edges_size_type num_edges (const Graph& graph) {
            // <your code>
            edges_size_type s = 1; // fix
            return s;}

        // ------------
        // num_vertices
        // ------------

        /**
         * returns the number of vertices in the graph
         */
        friend vertices_size_type num_vertices (const Graph& graph) {
            // <your code>
            vertices_size_type s = graph.g.size(); 
            return s;}

        // ------
        // source
        // ------

        /**
         * returns the starting point of the edge.
         * always returns the source of the edge, even if it does not exist in this graph
         */
        friend vertex_descriptor source (edge_descriptor e, const Graph& graph) {
            // <your code>
            vertex_descriptor v = 0; // fix
            return v;}

        // ------
        // target
        // ------

        /**
         * returns the vertex being pointed to.
         * always returns the target of the given edge, even if it does not exist in this graph
         */
        friend vertex_descriptor target (edge_descriptor e, const Graph& graph) {
            // <your code>
            vertex_descriptor v = 0; // fix
            return v;}

        // ------
        // vertex
        // ------

        /**
         * returns the nth vertex desciptor. Basically just returns the number given
         */
        friend vertex_descriptor vertex (vertices_size_type n, const Graph& graph) {
            // <your code>
            vertex_descriptor vd = n; // fix
            return vd;}

        // --------
        // vertices
        // --------

        /**
         * Returns two iterators that start at the beginning and (end + 1) of the vertices
         * 
         */
        friend std::pair<vertex_iterator, vertex_iterator> vertices (const Graph& graph) {
            // <your code>
            static int a [] = {0, 0};     // dummy data
            vertex_iterator b = a;
            vertex_iterator e = a + 2;
            return std::make_pair(b, e);}

    private:
        // ----
        // data
        // ----

        // boost uses a vector to store vertices
        // i'm guessing sets to store inside the vector
        std::set<edge_descriptor> edge_list;
        std::vector< std::set<vertex_descriptor> > g; // something like this

        // -----
        // valid
        // -----

        /**
         * <your documentation>
         */
        bool valid () const {
            // <your code>
            return true;}

    public:
        // ------------
        // constructors
        // ------------

        /**
         * <your documentation>
         */
        Graph () {
            // <your code>
            assert(valid());}

        // Default copy, destructor, and copy assignment
        // Graph  (const Graph<T>&);
        // ~Graph ();
        // Graph& operator = (const Graph&);
    };

#endif // Graph_h