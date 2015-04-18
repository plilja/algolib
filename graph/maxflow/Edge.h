#ifndef EDGE_H_
#define EDGE_H_


class Edge
{
public:
	Edge(int nodeFrom,int nodeTo, int capacity);
	virtual ~Edge();
	void setFlow(int flow);
	void setCapacity(int capacity);
	void setRestCapacity(int cfRemain);
	void setNodeFrom(int nodeFrom);
	void setNodeTo(int nodeTo);
	void setReverse(Edge *reverseEdge);
	void addToFlow(int amount);
	void addToCapacity(int amount);
	void addToRestCapacity(int amount);
	int getFlow();
	int getCapacity();
	int getRestCapacity();
	int getNodeFrom();
	int getNodeTo();
	Edge* getReverse();
private:
	int c,f,cf;
	int from, to;
	Edge *reverse;
};

#endif /*EDGE_H_*/
