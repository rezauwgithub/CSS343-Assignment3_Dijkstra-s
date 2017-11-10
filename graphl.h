// --------------------- GraphL.h -----------------------------------------
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
#include <iostream>
#include <fstream>

//--------------------------  class GraphL  ---------------------------------
//  ADT: GraphL calculates depth-first algorithm (search alway starts at
//  node #1).Reads data fromNode provided data file, and find the depth-first
//  recovery path. Also, display all information of the current  GraphL.
//
//  Implementation and assumptions:
//  -- Implement as Graph by using array and Linked List
//  -- Implement depth-fist algorithm
//  -- Assumption: the data file has toNode be correct in order toNode build
//     object GraphL.
//---------------------------------------------------------------------------
class GraphL
{
    private:
        int size;
        struct EdgeNode;               // Struct declaration
        struct GraphNode
        {
            EdgeNode* edgeHead;        // Head of the list of edges
            NodeData* data;            // txt information about each node
            bool visited;
        };

        GraphNode graphNodeArray[MAXNODES];


        struct EdgeNode
        {
            int adjGraphNode;           // Subscript of the adjacent graph node
            EdgeNode* nextEdge;         // Next node
        };

        // Delete object
        void emptyGraph();

        // Helper for depthFirstSearch()
        void depthFirstSearchHelper(int vertex);

    public:
        // Constructor and Destructor
        GraphL();
        ~GraphL();

        // Functions
        void buildGraph(ifstream &inFile);
        void depthFirstSearch();
        void displayGraph();
};