/*
 * Author: Patrik Lilja
 * Date: 07-09-18
 */ 

#include <iostream>
#include "Suffixarray.h"

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
	pair<long long int, int> *suff=new pair<long long int, int>[size];
	vector<pair<long long int, int> >::iterator it;
	int passes=(int) ceil(log(base.length()));
	int *rank=new int[size], j, startPos, endPos;
	long long int oldRank;
	for(int i=0; i<size; i++)
	{
		suff[i]=make_pair((int) base.at(i), i);
		rank[i]=(int) base.at(i);
	}
	for(int i=0; i<passes; i++)
	{
		cout<<"en ggn till"<<endl;
		j=0;
		for(int i=0; i<size; i++)
		{
			cout<<suff[i]->first<<" "<<it->second<<" rank: "<<rank[it->second]<<endl;
			j++;
		}
		sort(suff.begin(), suff.end());
		j=0;
		oldRank=0;//MAX_STRING_LENGTH+1;
		startPos=0;
		endPos=0;
		for(it=suff.begin(); it!=suff.end(); it++)
		{
			if(oldRank<it->first)
			{
				oldRank=it->first;
				sort(suff.at())
				j++;
			}
			rank[it->second]=j;
			endPos++;
		}
		j=0;
		for(it=suff.begin(); it!=suff.end(); it++)
		{
			j=it->second;
			
			it->first=rank[j]*MAX_STRING_LENGTH;
			if(j+(int)pow(2, i)<size)
			{
				it->first += rank[j+(int)pow(2, i)];
				//cout<<"j: "<<j<<" oldrank " <<rank[j+(int)pow(2, i)]<<" limit "<<j+(int)pow(2, i)<<endl;
				//cout<<it->first<<endl;
			}
		}	
	}
	j=0;
	for(it=suff.begin(); it!=suff.end(); it++)
	{
		sorted[j]=it->second;
		j++;
	}
	cout<<"slut"<<endl;	
	j=0;
	for(it=suff.begin(); it!=suff.end(); it++)
	{
		cout<<it->first<<" "<<it->second<<" rank: "<<rank[it->second]<<endl;
		j++;
	}
	
}
