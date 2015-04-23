/*
 * The indexmap class is a collection that stores objects
 * and associates integers with those objects. 
 * 
 * Given an integer an object can be retrived in constant time.
 * 
 * An object can be inserted in time O(1). 
 */
#pragma once

#include <vector>
#include <string>
#include <unordered_map>

template<typename T>
class indexmap
{
private:
    std::vector <T> ind; //Maps int->T
    std::unordered_map<T, int> objects; //Maps T->int
public:

    indexmap()
    {
    }

    /*
     * Insert an object in the map. Returns the index ascociated with
     * the object. The index returned will start at 0 for the first
     * object inserted and increase by 1 for each object inserted.
     *
     * If the object already is in the map, the index it was given when it was
     * first inserted will be returned.
     *
     * Runs in time O(1)
     */
    int get_index(T o)
    {
        std::pair<T, int> p(o, ind.size());
        auto r = objects.insert(p);
        if (r.second) {
            ind.push_back(o);
        }
        return r.first->second;
    }

    /*
     * Get the object ascociated with the integer i. The integer must be
     * already be ascociated with an object in the map.
     *
     * Runs in time O(1)
     */
    T get_object(int i)
    {
        return ind[i];
    }

    /*
     * Get the current size of the indexmap.
     *
     * Runs in time O(1)
     */
    int size()
    {
        return ind.size();
    }
};

