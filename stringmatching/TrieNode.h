/*
 * Author: Patrik Lilja
 * Date: 07-09-16

 * A TrieNode represents a node in a Trie data structure. 
 * 
 * This particular TrieNode is optimized to be used in the 
 * Aho-Corasick pattern matching algorithm. 
 * 
 * A TrieNode has a number of transitions to other TrieNodes.
 * It also has a failure function and maintains a list
 * of patterns that end in the node. 
 */ 

#ifndef TRIENODE_H_
#define TRIENODE_H_
#include <set>
#include <vector>
#include <map>

using std::vector;
using std::set;
using std::map;

typedef unsigned char uchar;

class TrieNode
{
public:
	TrieNode(TrieNode* root);
	
	/*
	 * Constructor to create the root node. 
	 */
	TrieNode();
	
	/*
	 * Destructor. 
	 */
	virtual ~TrieNode();
	
	/*
	 * Add a bridge to node n using char c.
	 */
	void addBridge(uchar c, TrieNode* n);
	
	/*
	 * Add the index of a word that ends in
	 * this node.
	 */
	void addEndWord(int wordIndex);
	
	/*
	 * Returns true if there exists a transition
	 * from char c.
	 */
	bool hasBridge(uchar c);
	
	/*
	 * Get the transition that char c leads to. 
	 */
	TrieNode* getBridge(uchar c);
	
	/*
	 * Get the root node. 
	 */
	TrieNode* getRoot();
	
	/*
	 * Set the failure function for this node.
	 * 
	 * That is the node that will be jumped to in case of failure
	 * to find a transition. 
	 */
	void setFail(TrieNode* n);

	/*
	 * Get the failure function for this node.
	 * 
	 * That is the node that will be jumped to in case of failure
	 * to find a transition. 
	 */
	TrieNode* getFail();
	
	/*
	 * Get a set containing the words that end in this node.
	 */
	set<int>* getEndWords();
	
	/*
	 * Merge end words with node t. That is, put every end word that
	 * t has that this node hasn't and add it to the list of end words.
	 * 
	 * t doesn't change. 
	 */
	void mergeEndWords(TrieNode* t);
	
	/*
	 * Clear this node.
	 * 
	 * I.e clears the transitions and the end words. 
	 */
	void clear();
	
	/*
	 * Get the transitions leading out of this node. 
	 */
	map<uchar, TrieNode*>* getTransitions();
private:
	TrieNode* root;
	TrieNode* fail;
	map<uchar, TrieNode*> transitions; 
	set<int> wordsThatEndHere;
};

#endif /*TRIENODE_H_*/
