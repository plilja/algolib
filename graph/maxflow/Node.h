/*
 * Author: Patrik Lilja
 * Date: 07-10-05
 */ 
#ifndef NODE_H_
#define NODE_H_

#include <list>
#include "Edge.h"

class Node:public std::list<Edge>
{
public:
	Node();
	Node(int n);
	virtual ~Node();
	int getNumber(){return name;}
	int flowFrom();
	int flowTo();
private:
	int name;
};

#endif /*NODE_H_*/
