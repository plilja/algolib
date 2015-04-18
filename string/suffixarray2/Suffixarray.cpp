/*
 * Author: Patrik Lilja
 * Date: 07-09-18
 */ 

#include <iostream>
#include <math.h>
#include "Suffixarray.h"

typedef long long int llint;

Suffixarray::Suffixarray(string s)
{
	base=s;
	sorted=new int[s.length()];
	size=s.length();
	suffixSort();
}

Suffixarray::~Suffixarray()
{
	delete[] sorted;
}

int Suffixarray::getElementAt(int i)
{
	return sorted[i];
}

void Suffixarray::suffixSort()
{
	pair<llint, int> *suff=new pair<llint, int>[size];
	llint *rank=new llint[size],  startPos, endPos, p;
	llint oldRank;
	//Begin with sorting on the first character
	for(int i=0; i<size; i++)
	{
		suff[i]=make_pair((int) base.at(i), i);
		rank[i]=(int) base.at(i);
	}
	sort(suff, suff+size);
	llint H=1;
	
	//Now use the result from previous sorting round in the next round
	while(H<size)
	{
		//First give every suffix a new rank based on it's current rank
		//and the rank of it's remaining letters.
		p=0;
		oldRank=0;
		for(int j=0; j<size; j++)
		{
			p=suff[j].second;
			suff[j].first=rank[p]*MAX_STRING_LENGTH;
			if(p+H<size)
			{
				suff[j].first += rank[p+H];
			}
		}
		
		//Now sort the array in chunks. The were determined the previous round.
		oldRank=rank[suff[0].second];
		startPos=0;
		endPos=0;
		for(int j=1; j<size; j++)
		{
			if(oldRank<rank[suff[j].second])
			{
				oldRank=rank[suff[j].second];
				sort(suff+startPos, suff+j);
				startPos=j;
			}
		}
		if(startPos<size)
		{
			sort(suff+startPos, suff+size);
		}
		
		//Reindex the rank from 0 to avoid overflow
		p=0;
		oldRank=0;
		for(int j=0; j<size; j++)
		{
			if(oldRank<suff[j].first)
			{
				oldRank=suff[j].first;
				p++;
			}
			rank[suff[j].second]=p;
		}
		
		H=H*2;
	}//end while(H<size)
	
	for(int j=0; j<size; j++)
	{
		sorted[j]=suff[j].second;
	}
	delete[] suff;
	delete[] rank;
}
