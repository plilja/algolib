/*
 * Author: Patrik Lilja
 * Date: 07-09-18
 */ 

#include <iostream>
#include <math.h>
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
	//vector<pair<long long int, int> >::iterator it;
	int passes=(int) ceil(log2(base.length()));
	//cout<<"passes: "<<passes<<" size: "<<size<<endl;
	int *rank=new int[size],  startPos, endPos, p;
	long long int oldRank;
	for(int i=0; i<size; i++)
	{
		suff[i]=make_pair((int) base.at(i), i);
		rank[i]=(int) base.at(i);
	}
	sort(suff, suff+size);
		/*for(int j=0; j<size; j++)
		{
			cout<<suff[j].first<<" "<<suff[j].second<<" rank: "<<rank[suff[j].second]<<endl;
		}*/
	int pow2_i;
	for(int i=0; i<passes; i++)
	{
//		cout<<pow(2,i)<<" i "<<i<<endl;
		p=0;
		oldRank=0;
		/*cout<<"innnan3 Sort"<<endl;
		for(int j=0; j<size; j++)
		{
			cout<<suff[j].first<<" "<<suff[j].second<<" rank: "<<rank[suff[j].second]<<endl;
		}*/
		/*for(int j=0; j<size; j++)
		{
		//	cout<<"indexs "<<suff[j].second<<endl;
			if(oldRank<suff[j].first)
			{
				oldRank=suff[j].first;
				p++;
			}
			rank[suff[j].second]=p;
		}*/
		

		pow2_i=(int) pow(2, i);
		for(int j=0; j<size; j++)
		{
			p=suff[j].second;
			suff[j].first=rank[p]*MAX_STRING_LENGTH;
			if(p+(int)pow(2, i)<size)
			{
				
				suff[j].first += rank[p+pow2_i];
//				cout<<"j: "<<j<<" oldrank " <<rank[j+(int)pow(2, i)]<<" limit "<<j+(int)pow(2, i)<<endl;
				//cout<<it->first<<endl;
			}
		}
		/*cout<<"efter Sort"<<endl;
		for(int j=0; j<size; j++)
		{
			cout<<suff[j].first<<" "<<suff[j].second<<" rank: "<<rank[suff[j].second]<<endl;
		}	*/		



		//sort(suff.begin(), suff.end());
		//sort(suff, suff+size);
		/*p=0;
		oldRank=rank[suff[0].second];//MAX_STRING_LENGTH+1;
		startPos=0;
		endPos=0;
		for(int j=1; j<size; j++)
		{
			if(oldRank<rank[suff[j].second])
			{
				oldRank=rank[suff[j].second];
				sort(suff+startPos, suff+j);
			//	cout<<"startpos "<<startPos<<" endpos "<<j<<endl;
				startPos=j;
				//p++;
			}
//			rank[suff[j].second]=p;
		}
		//cout<<"startpos "<<startPos<<" endpos "<<endPos<<endl;
		
		if(startPos<size)
		{
			sort(suff+startPos, suff+size);
		}*/
	}
	for(int j=0; j<size; j++)
	{
		sorted[j]=suff[j].second;
	}
//	cout<<"slut"<<endl;
	/*cout<<"slut"<<endl;	
	for(int j=0; j<size; j++)
	{
		cout<<suff[j].first<<" "<<suff[j].second<<" rank: "<<rank[suff[j].second]<<endl;
	}*/
	///delete[] suff;
	//delete[] rank;
}
