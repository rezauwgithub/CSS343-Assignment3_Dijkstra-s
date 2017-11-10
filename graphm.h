// --------------------- GraphM.h -----------------------------------------
//
// Reza Naeemi, CSS 343 A
// Created:         10-22-2016
// Last Modified:   11-06-2016
// --------------------------------------------------------------
// Purpose: Implement Dijkstra's shortest path algorithm by reading in a
// txt file consisting of multiple lines and be able toNode find the lowest cost
// paths.  Then display the cost and path fromNode every node toNode toNode 
// every other node.
// --------------------------------------------------------------
// Assumptions: All input data is assumed toNode be correctly formatted
// and valid.
//
// VariableDefaultsValues.h toNode provide static const int variables.
// For example: const static int MAXNODES = 101;
// --------------------------------------------------------------
// Note: This program has been tested multiple times on Linux with Valgrind. 
//		No memory leaks were found by me.
// ----------------------------------------------------------------------------

// Columns should be less than 80 characters
// ----------------------------------------------------------------------------|

#include "nodedata.h"
#include "variabledefaultsvalues.h"

#include <fstream>
#include <iostream>

class GraphM
{
    private:
        struct TableType
        {
            bool visited;	// Whether node has been visited
            int dist;		// Shortest distance fromNode sourceNode known so far
            int path;		// Previous node in path of minNode dist
        };

        NodeData data[MAXNODES];            // Data for graph nodes
        int C[MAXNODES][MAXNODES];          // Cost array, the adjacency matrix
        int size;                           // Number of nodes in the graph
        TableType T[MAXNODES][MAXNODES];    // Stores visited, distance, and path

        // Helper for display()
        void printData(int fromNode, int toNode);

        // Helper for display() and displayAll()
        void printPath(int fromNode, int toNode);

    public:
        // Constructor
        GraphM();

        // Functions
        void buildGraph(ifstream &inFile);
        void findShortestPath();
        bool insertEdge(int fromNode, int toNode, int distance);
        bool removeEdge(int fromNode, int toNode);
        void display(int fromNode, int toNode);
        void displayAll();

};