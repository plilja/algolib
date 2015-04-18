#pragma once

#include <vector>
#include <unordered_map>

struct DisjointSetNode {
    DisjointSetNode *parent;
    int rank;
};

class DisjointSet {
private:
    DisjointSetNode *find(int x);

    std::vector<DisjointSetNode> nodes;
    int _count;
public:
    DisjointSet(int size);
    virtual ~DisjointSet();

    /**
     * Merges the set containing x and y.
     */
    void merge(int x, int y);

    /**
     * Returns the number of sets.
     */
    int count();
};
