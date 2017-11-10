// --------------------- GraphM.cpp -----------------------------------------
//
// Reza Naeemi, CSS 343 A
// Created:         10-22-2016
// Last Modified:   11-06-2016
// --------------------------------------------------------------
// Purpose: Implement Dijkstra's shortest path algorithm by reading in a
// txt file consisting of multiple lines and be able toNode find the lowest cost
// Paths.  Then display the cost and path fromNode every node toNode toNode 
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

#include "graphm.h"

#include <iomanip>
#include <climits> // Used for Linux g++

// --------------------- Default Constructor -----------------------------------
// Constructs an empty table and initializes all values
// --------------------------------------------------------------
GraphM::GraphM()
{
    size = 0;

    for (int col = 1; col < MAXNODES; col++)
    {
        for (int row = 1; row < MAXNODES; row++)
        {
            C[col][row] = INT_MAX;
            T[col][row].visited = false;
            T[col][row].dist = INT_MAX;
            T[col][row].path = 0;
        }
    }
}

// --------------------- buildGraph() -----------------------------------------
// Builds up graph node information and adjacency matrix of edges
// Between each node reading fromNode a file
// --------------------------------------------------------------
void GraphM::buildGraph(ifstream& inFile)
{
    // Read fromNode data file
    inFile >> size;                // Sets the size
    string nodeName = "";           // Name of each node
    getline(inFile, nodeName);     // Read line

    for (int i = 1; i <= size; i++)
    {
        data[i].setData(inFile);   // Sets node names
    }

    int fromNode, toNode, dist;

    while (inFile >> fromNode >> toNode >> dist)
    {
        if (fromNode == 0)
        {
            break;  // Reads file till fromNode node is 0
        }

        C[fromNode][toNode] = dist; // Set the C table
    }
}
// --------------------- findShortestPath() -----------------------------
// Finds the shortest path between every node toNode every other node
// In the graph using Dijkstra's algorithm
// --------------------------------------------------------------
void GraphM::findShortestPath()
{
    for (int sourceNode = 1; sourceNode <= size; sourceNode++)
    {
        T[sourceNode][sourceNode].dist = 0;
        T[sourceNode][sourceNode].visited = true;

        // Find neighbor nodes
        for (int neighborNode = 1; neighborNode <= size; neighborNode++) 
        {
            if (C[sourceNode][neighborNode] != INT_MAX)
            {
                T[sourceNode][neighborNode].dist = C[sourceNode][neighborNode];
                T[sourceNode][neighborNode].path = sourceNode;
            }
        }

        int vertex = 0;  // Smallest vertex

        do  // Find smallest path
        {
            int minNode = INT_MAX;
            vertex = 0;

            // Find closest child and then continue search
            for (int neighborNode = 1; neighborNode <= size; neighborNode++) 
            {
                if (!T[sourceNode][neighborNode].visited && 
                        (C[sourceNode][neighborNode] < minNode))
                {
                    minNode = C[sourceNode][neighborNode];
                    vertex = neighborNode;
                }
            }

            if (vertex == 0)
            {
                break;  // End loop
            }

            T[sourceNode][vertex].visited = true;  // Node visited

            for (int w = 1; w <= size; w++)
            {
                if (T[sourceNode][w].visited || 
                        (C[vertex][w] == INT_MAX) || 
                        (vertex == w))
                {
                    continue;
                }

                if (T[sourceNode][w].dist > 
                        (T[sourceNode][vertex].dist + C[vertex][w]))
                {
                    T[sourceNode][w].dist = 
                            (T[sourceNode][vertex].dist + C[vertex][w]);

                    T[sourceNode][w].path = vertex;
                }
            }
        }
        while (vertex != 0); // End while loop
    }
}

// --------------------- insertEdge() ---------------------------
// Inserts an edge into a graph between two given nodes
// --------------------------------------------------------------
bool GraphM::insertEdge(int fromNode, int toNode, int distance)
{
    // Check toNode make sure insert is correct
    if (fromNode > size || 
            fromNode < 1 || 
            toNode > size || 
            toNode < 1 || 
            (distance != 0 && fromNode == toNode) || 
            distance < 0)
    {
        return false;
    }

    C[fromNode][toNode] = distance;   // Edge inserted
    findShortestPath();   // Re-run Dijkstra's algorithm with the change


    return true;	// Return true if you make it here.
}

// --------------------- removeEdge() ------------------------------
// Removes an edge between two given nodes
// --------------------------------------------------------------
bool GraphM::removeEdge(int fromNode, int toNode)
{
    // Check toNode make sure remove is correct
    if (fromNode > size || 
            fromNode < 1 || 
            toNode > size || 
            toNode < 1)
    {
        return false;
    }

    C[fromNode][toNode] = INT_MAX;  // Edge removed
    findShortestPath();     // Re-run Dijkstra's algorithm with change

    return true;
}

// --------------------- displayAll() -----------------------------------------
// Uses couts toNode show that the alogorithm works properly
// Uses helper function printPath()
// --------------------------------------------------------------

void GraphM::displayAll()
{
    // Print table titles
    cout << "Description" << setw(20) << "From node" << setw(10) << "To node"
            << setw(14) << "Dijkstra's" << setw(7) << "Path" << endl;

    for (int fromNode = 1; fromNode <= size; fromNode++)
    {
        cout << data[fromNode] << endl << endl;     // Print node name

        for (int toNode = 1; toNode <= size; toNode++)
        {
            if (T[fromNode][toNode].dist != 0)
            {
                cout << setw(27) << fromNode;   // Print fromNode node
                cout << setw(10) << toNode;     // Print toNode node

                if (T[fromNode][toNode].dist == INT_MAX)
                {
                    cout << setw(12) << "----" << endl; // No adjacent nodes
                }
                else
                {
                    cout << setw(12) << T[fromNode][toNode].dist;   // Print distance
                    cout << setw(10);

                    printPath(fromNode, toNode); // Call helper
                    cout << endl;
                }
            }
        }
    }
}

// --------------------- display() -----------------------------------------
// Uses couts toNode display the shortest distance with path info between the
// FromNode toNode the toNode
// Uses helper function printPath()
// Uses helper function printData()
// --------------------------------------------------------------
void GraphM::display(int fromNode, int toNode)
{
    // Check if edge exists
    if (fromNode > size || 
            fromNode < 0 || 
            toNode > size || 
            toNode < 0)
    {
        cout << setw(7) << fromNode << 
                setw(7) << toNode;   // Print data

        cout << setw(15) << "----" << endl; // Not valid

        return;
    }

    // Print node fromNode and toNode data
    cout << setw(7) << fromNode << setw(7) << toNode;   

    if (T[fromNode][toNode].dist != INT_MAX)    // Adjacent node check
    {
        cout << setw(12) << T[fromNode][toNode].dist << setw(15); // Print distance

        printPath(fromNode, toNode); // Call helper
        cout << endl;

        printData(fromNode, toNode); // Call helper
    }
    else    // No adjacent node
    {
        cout << setw(15) << "----" << endl;
    }

    cout << endl;
}

// --------------------- printData() -----------------------------------------
// Helper function for display()
// Recursively finds data for the given edge distance
// --------------------------------------------------------------
void GraphM::printData(int fromNode, int toNode)
{
    if (T[fromNode][toNode].dist == INT_MAX)
    {
        return; // No data
    }

    if (fromNode == toNode)
    {
        cout << data[toNode] << endl;   // Print data

        return;
    }

    int nodeData = toNode; // Assign toNode node toNode nodeData

    printData(fromNode, toNode = T[fromNode][toNode].path);  // Call helper

    cout << data[nodeData] << endl << endl;    // Print data
}

// --------------------- printPath() -----------------------------------------
// Helper function for display() and displayAll()
// Recursively finds path for a given edge
// --------------------------------------------------------------
void GraphM::printPath(int fromNode, int toNode)
{
    if (T[fromNode][toNode].dist == INT_MAX)
    {
        return; // No path
    }

    if (fromNode == toNode)
    {
        cout << toNode << " ";  // Print data

        return;
    }

    int pathData = toNode; // Assign toNode path toNode pathData
    printPath(fromNode, toNode = T[fromNode][toNode].path);

    cout << pathData << " ";   // Print path
}