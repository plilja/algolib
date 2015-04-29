#pragma once

#include <vector>

#include <string>

/*
 * An implementations of the Aho-Corasick pattern matching algorithm. 
 * 
 * Time-complexity is O(text.length+sum(patterns.length)+#hits)
 * 
 * Parameters:
 * text: The text to search through
 * patterns: The patterns to search for.
 * 
 * Returns:
 * Vector of vectors where an inner vector v_i contains the indexes
 * where the i:th patterns has been found in the text. Indexes start
 * at 0 for the first position in the text.
 */
std::vector<std::vector<int> > ahocorasick(const std::string &text, const std::vector<std::string> &patterns);


