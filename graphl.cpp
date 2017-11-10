// --------------------- GraphL.cpp -----------------------------------------
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
// --------------------------------------------------------------
// Note: This program has been tested multiple times on Linux with Valgrind. 
//		No memory leaks were found by me.
// ----------------------------------------------------------------------------

// Columns should be less than 80 characters
// ----------------------------------------------------------------------------|
#include "graphl.h"

#include <iomanip>

// --------------------- GraphL() -----------------------------------------
// Default constructor
// --------------------------------------------------------------
GraphL::GraphL()
{
    size = 0;

    for (int i = 1; i < MAXNODES; i++){
        graphNodeArray[i].edgeHead = NULL;
        graphNodeArray[i].data = NULL;
		graphNodeArray[i].visited = false;
    }
}

// --------------------- ~GraphL() -----------------------------------------
// Destructor
// --------------------------------------------------------------
GraphL::~GraphL()
{
    emptyGraph();
}

// --------------------- emptyGraph() -----------------------------------------
// Deletes object
// Helper function for Destructor
// --------------------------------------------------------------
void GraphL::emptyGraph()
{
    for (int i = 1; i <= size; i++)
    {
        graphNodeArray[i].visited = false;
        delete graphNodeArray[i].data;  // Delete edge name
        graphNodeArray[i].data = NULL;  // Set edge name toNode NULL

        if (graphNodeArray[i].edgeHead != NULL) // Check for Linked List 
												// in array index
        {
            EdgeNode* deleteMe = graphNodeArray[i].edgeHead;

            while (deleteMe != NULL) // Traverse Linked List
            {
                graphNodeArray[i].edgeHead = graphNodeArray[i].edgeHead->nextEdge;
                delete deleteMe; // Delete node
                deleteMe = NULL; // Set node toNode NULL
                deleteMe = graphNodeArray[i].edgeHead;   // Move head
            }
        }
    }
}

// --------------------- buildGraph() -----------------------------------------
// Builds up graph node information and adjacency list of edges between each
// Node reading fromNode a data file
// --------------------------------------------------------------
void GraphL::buildGraph(ifstream &inFile)
{
    // Read fromNode data file
    inFile >> size;            // Sets the size
    string nodeName = "";       // Name of each node
    getline(inFile, nodeName); // Read line

    for (int i = 1; i <= size; i++) // Insert edge names
    {
        getline(inFile, nodeName);
        NodeData* temp = new NodeData(nodeName);
        graphNodeArray[i].data = temp;   // Insert into array
    }

    int fromNode, toNode;

    while (inFile >> fromNode >> toNode)   // Fill Linked List
    {
        if (fromNode == 0)
        {
            break;
        }

        if (graphNodeArray[fromNode].edgeHead == NULL)  // First node at array index
        {
            EdgeNode* node = new EdgeNode;
            node->adjGraphNode = toNode;            // Insert adjacent
            graphNodeArray[fromNode].edgeHead = node;   // Point toNode head
            graphNodeArray[fromNode].edgeHead->nextEdge  = NULL;
        }
        else    // Additional nodes in Linked List
        {
            EdgeNode* node = new EdgeNode;
            node->adjGraphNode = toNode;            // Insert adjacent
            node->nextEdge = graphNodeArray[fromNode].edgeHead;  // Move pointer
            graphNodeArray[fromNode].edgeHead = node;  // Assign as head
        }
    }
}

// --------------------- depthFirstSearch() -----------------------------------------
// Makes a depth-first search and displays each node in depth-first order
// --------------------------------------------------------------
void GraphL::depthFirstSearch()
{
    cout << "Depth-first ordering:"; 

    for (int vertex = 1; vertex <= size; ++vertex) // Loop through size
    {
        if (!graphNodeArray[vertex].visited)   // Check if node has been visited
        {
            depthFirstSearchHelper(vertex);  // Call helper
        }
    }

    cout << endl;
}

// --------------------- depthFirstSearchHelper() -----------------------------------
// Helper function for depthFirstSearch()
// Recursively finds the depthFirstSearch
// --------------------------------------------------------------
void GraphL::depthFirstSearchHelper(int vertex)
{
    cout << setw(2) << vertex;   // Print node
    graphNodeArray[vertex].visited = true;   // Mark visited
    EdgeNode* current = graphNodeArray[vertex].edgeHead; // Move pointer toNode head

    while (current != NULL) // Loop till end of Linked List
    {
        if (!graphNodeArray[current->adjGraphNode].visited) // Check if visited
        {
            depthFirstSearchHelper(current->adjGraphNode);  // Call helper
        }

        current = current->nextEdge;    // Move pointer toNode next node in Linked List
    }
}

// --------------------- displayGraph() -----------------------------------------
// Displays each node information and edge in the graph
// --------------------------------------------------------------
void GraphL::displayGraph()
{

    cout << "Graph:" << endl;

    for (int i = 1; i <= size; i++) // Print array info
    {
        // Print index and name of the node
        cout << "Node" << i << "      " << *graphNodeArray[i].data << endl << endl;

        EdgeNode* current = graphNodeArray[i].edgeHead; // Assign toNode current

        while (current != NULL) // Check for Linked List
        {
            // Print Linked List
            cout << setw(7) << "edge " << i << 
				setw(2) << current->adjGraphNode << endl;

            current = current->nextEdge;  // Move pointer toNode next node in Linked List
        }
    }
}
