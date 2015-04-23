/*
 * This Suffixarray class is used to create a sorted suffix array
 * from a string. The array will store the suffixes of the string 
 * sorted in lexicographic order. 
 */
#pragma once

#include <string>
#include <vector>

#define MAX_STRING_LENGTH 1000000

class Suffixarray
{
public:

    /*
     * Construct a suffix array from string s. The
     * construction runs in time O(n*(log n)^2).
     *
     * The suffix array will be immutable.
     */
    Suffixarray(const std::string &s);

    /*
     * Returns the the index in the string of the
     * i:th smallest suffix.
     *
     * Runs in O(1)
     */
    int get_element_at(int i);

private:
    std::string base;
    std::vector<int> sorted;
    int size;

    void suffix_sort();
};

