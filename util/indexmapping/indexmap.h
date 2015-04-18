/*
 * Author: Patrik Lilja
 * Date: 07-09-11
 * 
 * The indexmap class is a collection that stores strings
 * and associates integers with those string. 
 * 
 * Given an integer a string can be retrived in constant time.
 * 
 * A string can be inserted in time O(log n). 
 */
#ifndef INDEXMAP_H_
#define INDEXMAP_H_

#include <vector>
#include <string>
#include <unordered_map>

class indexmap
{
public:

	indexmap();

	virtual ~indexmap();
	
	/*
	 * Insert string s in the map. Returns the index ascociated with
	 * the string. The index returned will start at 0 for the first
	 * object inserted and increase by 1 for each object inserted. 
	 * 
	 * If the string already is in the map, the index it was given when it was
	 * first inserted will be returned. 
	 * 
	 * Runs in time O(1)
	 */
	int getIndex(std::string s);
	
	/*
	 * Get the string ascociated with the integer i. The integer must be 
	 * already be ascociated with a string in the map. 
	 * 
	 * Runs in time O(1)
	 */
    std::string getObject(int i);
	
	/*
	 * Get the current size of the indexmap. 
	 * 
	 * Runs in time O(1)
	 */
	int size();
private:
    std::vector<std::string> ind; //Maps int->string
    std::unordered_map<std::string, int> objects; //Maps string->int
};

#endif /*INDEXMAP_H_*/
