#include <vector>
#include <unordered_map>

#pragma once

struct DisjointSetNode {
    DisjointSetNode *parent;
    int rank;
};

template <typename T>
class DisjointSet {
private:
    DisjointSetNode* find_helper(DisjointSetNode *current) {
        if (current->parent != NULL) {
            current->parent = find_helper(current->parent);
            return current->parent;
        } else {
            return current;
        }
    }

    DisjointSetNode *find(T x)
    {
        DisjointSetNode *node = &nodes[id[x]];
        return find_helper(node);
   }

    std::vector<DisjointSetNode> nodes;
    int _count;
public:
    DisjointSet(int size)
    {
        nodes = std::vector<DisjointSetNode>(size, DisjointSetNode({NULL, -1}));
        _count = 0;
    }
    virtual ~DisjointSet()
    {
    }

    /**
     * Inserts a new element as a singleton contained set {x}.
     */
    void insert(T x)
    {
        DisjointSetNode &node = nodes[x];

        nodes.push_back(new_node);
        id[x] = nodes.size() - 1;
        _count++;

    }

    /**
     * Merges the set containing x and y.
     */
    void merge(T x, T y)
    {
        DisjointSetNode *x_root = find(x);
        DisjointSetNode *y_root = find(y);
        if (x_root == y_root)
            return; //already in same set

        if (x_root->rank < y_root->rank) {
            x_root->parent = y_root;
        } else if (x_root->rank > y_root->rank) {
            y_root->parent = x_root;
        } else {
            y_root->parent = x_root;
            x_root->rank = x_root->rank + 1;
        }
        _count--;

    }

    /**
     * Returns the number of sets.
     */
    int count()
    {
        return _count;
    }
};
