#include "Edge.h"

Edge::~Edge()
{
}


Edge::Edge(int nodeFrom,int nodeTo, int capacity){
	from = nodeFrom;
	to = nodeTo;
	c = cf = capacity;
	f = 0;
}

void Edge::setFlow(int flow){
	f = flow;
}

void Edge::setCapacity(int capacity){
	c = capacity;
}

void Edge::setRestCapacity(int cfRemain){
	cf = cfRemain;
}

void Edge::setNodeFrom(int nodeFrom){
	from = nodeFrom;
}

void Edge::setNodeTo(int nodeTo){
	to = nodeTo;
}

void Edge::setReverse(Edge *reverseEdge){
	reverse = reverseEdge;
}

void Edge::addToFlow(int amount){
	f = f+amount;
}

void Edge::addToCapacity(int amount){
	c = c+amount;
}

void Edge::addToRestCapacity(int amount){
	cf = cf+amount;
}

int Edge::getFlow(){
	return f;
}

int Edge::getCapacity(){
	return c;
}

int Edge::getRestCapacity(){
	return cf;
}

int Edge::getNodeFrom(){
	return from;
}

int Edge::getNodeTo(){
	return to;
}

Edge* Edge::getReverse(){
	return reverse;
}
