/*
 * An implementations of the Aho-Corasick pattern matching algorithm. 
 * 
 * The total number of characters in all of the patterns that are being 
 * searched may not exceed 100000. 
 * 
 * Se article below for a description of the algorithm. 
 * Aho, Alfred V.; Margaret J. Corasick (June 1975). 
 * "Efficient string matching: An aid to bibliographic search"
 */ 

#include <iostream>
#include <math.h>
#include <string>
#include <vector>
#define NDEBUG //Do we wan't assertions?
#include <cassert>
#include <queue>
#include "stringmultimatching.h"
#include "TrieNode.h"

using namespace std;


//I'm still bad at memory allocations and deallocations in C++,
//so I reuse preallocated ones. 
TrieNode nodes[100010]; 

/*
 * Phase 1 of Aho-Corasick algorithm. 
 * 
 * Construct the keyword trie. Each TrieNode that end a pattern
 * will list it in the TrieNode.getEndWords(). 
 * 
 * Parameters:
 * patterns: The patterns we are going to search for 
 * 
 * Return:
 * The root node of the trie described above.  
 */
TrieNode* constructKeywordTree(vector<string> patterns)
{
	/*for(int i=0; i<100005; i++)
	{
		nodes[i].clear();
	}*/
	string s;
	uchar c;
	TrieNode* root=&nodes[0];
	root->clear();
	TrieNode* current=root;
	TrieNode *tmp;
	vector<string>::iterator it;
	string::iterator sit;
	int i=0, firstFree=1;
	for(it=patterns.begin(); it!=patterns.end(); it++)
	{
		s=*it;
		current=root;
		for(sit=s.begin(); sit!=s.end(); sit++)
		{
			c=*sit;
			//If we can reuse a transition, do so,
			//otherwise pick a new node.
			if(current->hasBridge(c))
			{
				current=current->getBridge(c);
			}
			else
			{
				tmp=&nodes[firstFree];
				tmp->clear();
				current->addBridge(c, tmp);
				current=tmp;
				firstFree++;
			}
		}
		current->addEndWord(i);
		i++;
	}
	return root;
}

/*
 * Phase 1 of Aho-Corasick algorithm.
 * 
 * Add fail transitions to every node (except root=undefined), 
 * that should be followed in case a transition isn't possible.
 * 
 */
void constructFailTransitions(TrieNode* root)
{
	queue<TrieNode*> q;
	TrieNode *t, *v, *u, *goFail;
	for(map<uchar, TrieNode*>::iterator it=root->getTransitions()->begin(); it!=root->getTransitions()->end(); it++)
	{
		t=it->second;
		q.push(t);
		t->setFail(root);
	}
	uchar i;
	while(!q.empty())
	{
		t=q.front();
		q.pop();
		for(map<uchar, TrieNode*>::iterator it=t->getTransitions()->begin(); it!=t->getTransitions()->end(); it++)
		{
			i=it->first;
			u=it->second;
			q.push(u);
			v=t->getFail();
			while(v!=root && !(v->hasBridge(i)))
			{
				v=v->getFail();
			}
			goFail=v->getBridge(i);
			u->setFail(goFail);
			u->mergeEndWords(goFail);
		} 
	}
}

/*
 * Debug output for a trie. 
 */
void printTrie(uchar c, TrieNode *t)
{
	cout<<"Address "<<t<<" The following indexes end in "<<c<<" ";
	for(set<int>::iterator it=t->getEndWords()->begin(); it!=t->getEndWords()->end(); it++)
	{
		cout<<*it<<" ";
	}
	cout<<endl;
	cout<<"Fail transition for character "<<c<<" is "<<t->getFail()<<endl;
	queue<TrieNode*> q;
	for(uchar i=0; i<255; i++)
	{
		if(t->hasBridge(i))
		{
			cout<<"Character "<<c<<" has pointer to "<<i<<" ending indexes: ";
			cout<<endl;
			printTrie(i, t->getBridge(i));
		}
	}
}

vector< vector<int> > ahocorasick(string text, vector<string> patterns)
{
	int *lengths=new int[patterns.size()];
	int i=0;
	for(vector<string>::iterator it=patterns.begin(); it!=patterns.end(); it++)
	{
		lengths[i]=it->length();
		i++;
	}
	i=0;
	TrieNode* root=constructKeywordTree(patterns);
	constructFailTransitions(root);
	TrieNode* state=root;
	string::iterator it;
	uchar c;
	set<int>::iterator sit;
	vector< vector<int> > ans(patterns.size());
	for(it=text.begin(); it!=text.end(); it++)
	{
		c=*it;
		while(state!=root && !(state->hasBridge(c)))
		{
			state=state->getFail();
		}
		state=state->getBridge(c);
		for(sit=state->getEndWords()->begin(); sit!=state->getEndWords()->end(); sit++)
		{
			ans[*sit].push_back(i-lengths[*sit]+1);
		}
		i++;
	}
	//printTrie(' ',root);
	delete[] lengths;
	//delete root;
	return ans;
}

