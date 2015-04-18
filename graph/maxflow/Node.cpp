/*
 * Author: Patrik Lilja
 * Date: 07-10-05
 */ 
#include "Node.h"

static int firstFreeName=0;

Node::Node()
{
	name=firstFreeName;
	firstFreeName++;
}


Node::Node(int n)
{
	name=n;
	firstFreeName=n+1;
}

Node::~Node()
{
}

int Node::flowFrom()
{
	int flow=0;
	int temp;
	Edge *e;
	for(Node::iterator it=begin(); it!=end(); it++)
	{
		*e=*it;
		temp=e->getFlow();
		if(temp>0)
			flow += temp;
	}
	
	return flow;
}

int Node::flowTo()
{
	int flow=0;
	int temp;
	Edge *e;
	for(Node::iterator it=begin(); it!=end(); it++)
	{
		*e=*it;
		temp=e->getReverse()->getFlow();
		if(temp>0)
			flow += temp;
	}
	
	return flow;


}
