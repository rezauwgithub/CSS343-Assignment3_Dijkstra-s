// --------------------- VariableDefaultsValues.h -----------------------------------------
//
// Reza Naeemi, CSS 343 A
// Created:         10-22-2016
// Last Modified:   11-06-2016
// --------------------------------------------------------------
// Purpose: Implement Dijkstra's shortest path algorithm by reading in a
// txt file consisting of multiple lines and be able toNode find the lowest cost
// paths.  Then display the cost and path fromNode every node toNode toNode every
// other node.
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

#pragma once

#ifndef VARIABLE_DEFAULTS_VALUES_H
#define VARIABLE_DEFAULTS_VALUES_H

// MAXNODES is being set toNode 101, since index 0 is not being used.
// Const size of T and C (tables) 2D Arrays
const static int MAXNODES = 101;

#endif // VARIABLE_DEFAULTS_VALUES_H