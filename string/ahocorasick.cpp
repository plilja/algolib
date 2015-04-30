#include "ahocorasick.h"
#include <queue>
#include <set>
#include <map>
#include <memory>

using std::string;
using std::vector;
using std::set;
using std::map;
using std::shared_ptr;
using std::make_shared;

class TrieNode;

typedef unsigned char uchar;
typedef shared_ptr<TrieNode> TrieNodePtr;

class TrieNode {
public:
    TrieNode(TrieNodePtr _root) : root(_root)
    {
    }

    TrieNode()
    {
        root = TrieNodePtr(this);
    }

    /*
     * Add a bridge to node n using char c.
     */
    void addBridge(uchar c, TrieNodePtr n)
    {
        transitions[c] = n;
    }

    /*
     * Add the index of a word that ends in
     * this node.
     */
    void addEndWord(int wordIndex)
    {
        words_that_end_here.insert(wordIndex);
    }

    /*
     * Returns true if there exists a transition
     * from char c.
     */
    bool hasBridge(uchar c)
    {
        auto it = transitions.find(c);
        if (it != transitions.end()) {
            return true;
        }
        return false;
    }

    /*
     * Get the transition that char c leads to.
     */
    TrieNodePtr getBridge(uchar c)
    {
        auto it = transitions.find(c);
        if (it == transitions.end()) {
            return root;
        }
        return it->second;
    }

    TrieNodePtr getRoot()
    {
        return root;
    }

    /*
     * Set the failure function for this node.
     *
     * That is the node that will be jumped to in case of failure
     * to find a transition.
     */
    void setFail(TrieNodePtr n)
    {
        fail = n;
    }

    /*
     * Get the failure function for this node.
     *
     * That is the node that will be jumped to in case of failure
     * to find a transition.
     */
    TrieNodePtr getFail()
    {
        return fail;
    }

    set<int> &getEndWords()
    {
        return words_that_end_here;
    }

    /*
     * Merge end words with node t. That is, put every end word that
     * t has that this node hasn't and add it to the list of end words.
     *
     * t doesn't change.
     */
    void mergeEndWords(TrieNodePtr t)
    {
        set<int>::iterator it;
        set<int> &toMerge = t->getEndWords();
        for (it = toMerge.begin(); it != toMerge.end(); it++) {
            words_that_end_here.insert(*it);
        }
    }

    void clear()
    {
        transitions.clear();
        words_that_end_here.clear();
    }

    /*
     * Get the transitions leading out of this node.
     */
    map<uchar, TrieNodePtr> &getTransitions()
    {
        return transitions;
    }

private:
    TrieNodePtr root;
    TrieNodePtr fail;
    map<uchar, TrieNodePtr> transitions;
    set<int> words_that_end_here;
};

/*
 * Construct the keyword trie. Each TrieNode that end a pattern
 * will list it in the TrieNode.getEndWords().
 *
 * Return:
 * The root node of the trie described above.
 */
TrieNodePtr constructKeywordTree(const vector < string > &patterns)
{
    TrieNodePtr root = make_shared<TrieNode>();
    for (int i = 0; i < (int)patterns.size(); ++i) {
        auto &s = patterns[i];
        TrieNodePtr current = root;
        for (char c : s) {
            //If we can reuse a transition, do so,
            //otherwise pick a new node.
            if (current->hasBridge(c)) {
                current = current->getBridge(c);
            } else {
                auto tmp = make_shared<TrieNode>();
                tmp->clear();
                current->addBridge(c, tmp);
                current = tmp;
            }
        }
        current->addEndWord(i);
    }
    return root;
}

/*
 * Add fail transitions to every node (except root=undefined),
 * that should be followed in case a transition isn't possible.
 *
 */
void constructFailTransitions(TrieNodePtr root)
{
    std::queue < TrieNodePtr> q;

    for (auto &item : root->getTransitions()) {
        q.push(item.second);
        item.second->setFail(root);
    }

    while (!q.empty()) {
        auto t = q.front();
        q.pop();

        for (auto &item : t->getTransitions()) {
            uchar c = item.first;
            TrieNodePtr u = item.second;
            q.push(u);
            TrieNodePtr v = t->getFail();
            while (v != root && !(v->hasBridge(c))) {
                v = v->getFail();
            }
            TrieNodePtr go_fail = v->getBridge(c);
            u->setFail(go_fail);
            u->mergeEndWords(go_fail);
        }
    }
}

vector<vector<int>> search(const string &text, const vector<string> &patterns, TrieNodePtr root)
{
    TrieNodePtr state = root;
    int i = 0;
    vector <vector<int>> ans(patterns.size(), vector<int>());
    for (char c : text) {
        while (state != root && !(state->hasBridge(c))) {
            state = state->getFail();
        }
        state = state->getBridge(c);
        for (auto endw : state->getEndWords()) {
            ans[endw].push_back(i - patterns[endw].length() + 1);
        }
        i++;
    }
    return ans;
}

vector <vector<int>> ahocorasick(const string &text, const vector <string> &patterns)
{
    auto root = constructKeywordTree(patterns);
    constructFailTransitions(root);
    return search(text, patterns, root);
}

