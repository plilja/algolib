/*
 * Author: Patrik Lilja
 * Date: 07-09-11
 * 
 * This file solves the knapsack problem. 
 * 
 * It runs in time O(capacity*nrOfItems)
 */
#ifndef KNAPSACK_H_
#define KNAPSACK_H_

#include <vector>
#include <iostream>
#include <memory>

#define NEG_INF -2147483648
#define D_NEG_INF -2147483648.0
#define INF 2147483647

using namespace std;

/*
 * Solve the knapsack problem for a reasonable size of the sack and a
 * reasonable number of items.
 * 
 * Parameters:
 * sackCapacity - The capacity of the sack
 * nrOfItems - The number of items to choose from
 * items - list of items, the first value of each pair describes the value and the second describes it's weight
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
unique_ptr<vector<int> > knapsack(int sack_capacity, vector<pair<int,int> > items);

#endif /*KNAPSACK_H_*/
