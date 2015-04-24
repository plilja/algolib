/*
 * This file solves the knapsack problem. 
 * 
 * It runs in time O(capacity*nrOfItems)
 */
#pragma once

#include <vector>

/*
 * Solve the knapsack problem for a reasonable size of the sack and a
 * reasonable number of items.
 * 
 * Parameters:
 * items - list of items, the first value of each pair describes the value and the second describes it's weight
 * sackCapacity - The capacity of the sack
 *
 * Returns:
 * An vector with the indexes chosen in a solution to the problem, 
 * the indexes start with 0 for the first item. 
 * 
 * Runs in time O(c*n), where c is the sack capacity and n is the number of items
 * 
 * Se: http://en.wikipedia.org/wiki/Knapsack_problem
 * for description of the algorithm.  
 */
std::vector<int> knapsack(std::vector<std::pair<int,int>> items, int sack_capacity);

