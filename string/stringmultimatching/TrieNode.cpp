/*
 * Author: Patrik Lilja
 * Date: 07-09-16
 */ 

#include "TrieNode.h"
#include <iostream>

using namespace std;


TrieNode::TrieNode(TrieNode* root)
{
	this->root=root;
	
}

TrieNode::TrieNode()
{
	root=this;
}


TrieNode::~TrieNode()
{
	//BUGGY
	/*for(map<uchar, TrieNode*>::iterator it=transitions.begin(); it!=transitions.end(); it++)
	{
		delete it->second;
	}
	transitions.clear();
	wordsThatEndHere.clear();*/
}

void TrieNode::addBridge(uchar c, TrieNode* n)
{
	transitions[c]=n;
}

void TrieNode::addEndWord(int wordIndex)
{
	wordsThatEndHere.insert(wordIndex);
}

set<int>* TrieNode::getEndWords()
{
	return &wordsThatEndHere;
}

void TrieNode::mergeEndWords(TrieNode* t)
{
	set<int>::iterator it;
	set<int>* toMerge;
	toMerge=t->getEndWords();
	for(it=toMerge->begin(); it!=toMerge->end(); it++)
	{
		wordsThatEndHere.insert(*it);
	}
}

bool TrieNode::hasBridge(uchar c)
{
	map<uchar, TrieNode*>::iterator it=transitions.find(c);
	if(it!=transitions.end())
	{
		return true;
	}
	return false;
}

map<uchar, TrieNode*>* TrieNode::getTransitions()
{
	return &transitions;
	
}

void TrieNode::clear()
{
	transitions.clear();
	wordsThatEndHere.clear();
}

TrieNode* TrieNode::getBridge(uchar c)
{
	map<uchar, TrieNode*>::iterator it=transitions.find(c);
	if(it==transitions.end())
	{
		return root;
	}
	return it->second;
}

TrieNode* TrieNode::getRoot()
{
	return root;
}

void TrieNode::setFail(TrieNode* n)
{
	fail=n;
}

TrieNode* TrieNode::getFail()
{
	return fail;
}

