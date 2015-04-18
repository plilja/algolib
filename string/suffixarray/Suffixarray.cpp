#include <iostream>
#include <math.h>
#include <queue>
#include "Suffixarray.h"

using namespace std;

Suffixarray::Suffixarray(string s)
{
	str=s;
	pos=new int[s.length()];
	size=s.length();
	suffixSort();
}

Suffixarray::~Suffixarray()
{
	delete[] pos;
}

int Suffixarray::getElementAt(int i)
{
	return pos[i];
}

void Suffixarray::suffixSort2()
{
	vector<int> *buckets=new vector<int>[size];
	int *prm=new int[size];
	vector<int>::iterator it;

	//We start by performing a bucket sort on the first character in every suffix
	for(int i=0; i<size; i++)
	{
		buckets[(int)(unsigned char)str.at(i)].push_back(i);
	}
	int c=0, j;
	for(int a=0; a<255; a++) //255 is alphabet size
	{
		for(it=buckets[a].begin(); it!=buckets[a].end(); it++)
		{
			prm[*it]=c;
			c++;
		}
	}
	for(int i=0; i<size; i++)
	{
		pos[prm[i]]=i;
	}
	int H=1, left, right, d, e, len;
	while(H<size)
	{
		for(int i=size-1; i>=0; i--)
		{
			//buckets[i]
			
		}
		
		H=2*H;
		
		
	}
	


	
	
	
	delete[] buckets;
	
}

void Suffixarray::suffixSort()
{
	int *prm=new int[size];
	int *count=new int[size];
	for(int i=0; i<size; i++)
	{
		count[i]=0;
	}
	bool *BH=new bool[size+1];
	bool *B2H=new bool[size+1];
	vector<int> *buckets=new vector<int>[256];
	vector<int>::iterator it;
	
	//We start by performing a bucket sort on the first character in every suffix
	for(int i=0; i<size; i++)
	{
		buckets[(int)(unsigned char)str.at(i)].push_back(i);
	}
	int c=0, j;
	bool begin;
	for(int a=0; a<255; a++) //255 is alphabet size
	{
		begin=true;
		for(it=buckets[a].begin(); it!=buckets[a].end(); it++)
		{
			//j=
			prm[*it]=c;
			if(begin)
			{
				BH[c]=true;
				begin=false;
			}
			else
			{
				BH[c]=false;
			}
			c++;
		}
	}
	BH[size]=true;
	for(int i=0; i<size; i++)
	{
		pos[prm[i]]=i;
	}
	for(int i=0; i<size; i++)
	{
		cout<<BH[i]<<endl;
	}
	
	//Now perform sorting where each step is based on the result from the previous round.
	int H=1, left, right, d, e, len;
	while(H<size)
	{
		left=0;
		for(int i=0; i<size; i++)
		{
			if(BH[i])
			{
				left=i;
				count[left]=0;
			}
			prm[pos[i]]=left;
		}
		//DEBUG OUTPUT
		cout<<"BEGIN DEBUG"<<endl;
		for(int i=0; i<size; i++)
		{
			cout<<pos[i]<<" ";
		}
		cout<<endl;
		for(int i=0; i<size; i++)
		{
			cout<<prm[i]<<" ";
		}
		cout<<endl<<"SLUT DEBUG"<<endl;
		
		d=size-H;
		e=prm[d];
		prm[d]=e+count[e];
		count[e]++;
		B2H[prm[d]]=true;
		j=0;
		left=0;		
		while(true)
		{
/*			cout<<"prm: "<<prm[0]<<endl;
			if(prm[0]!=2)
			{
				cout<<"hoppla ";
			}
			cout<<" j: "<<j<<endl;*/
			begin=true;
			left=j;
			while(!BH[j] || begin)
			{
				begin=false;
				d=pos[j]-H;
				j++;
				if(d<0)
				{
					continue;
				}
				e=prm[d];
				prm[d]=e+count[e];
				cout<<"d "<<d<<" prm "<<prm[d]<<endl;
				count[e]++;
				B2H[prm[d]]=true;
			}
			j=left;
			begin=true;
			while(!BH[j] || begin)
			{
				begin=false;
				d=pos[j]-H;
				j++;
				if(d<0)
				{
					continue;
				}
				e=prm[d]+1;
				while(!BH[e] && B2H[e])
				{
					e++;
				}
				for(int i=prm[d]; i<e; i++)
				{
					B2H[i]=false;
				}
			}
			if(j>=size)
			{
				cout<<"slutar "<<j<<endl;
				break;
			}
			
		}
		for(int i=0; i<size; i++)
		{
			//cout<<"prmi: "<<prm[i]<<" i "<<i<<endl;
			pos[prm[i]]=i;
		}
		for(int i=0; i<size; i++)
		{
			//if(B2H[i] && !BH[i])
			//{
				BH[i]=B2H[i];
				
			//}
		}
		H=2*H;
		cout<<"H "<<H<<endl;
	}
	
	for(int i=0; i<size; i++)
	{
		cout<<pos[i]<<" ";
	}
	cout<<endl;
	
	
	delete[] buckets;
	delete[] B2H;
	delete[] BH;
	delete[] count;
	delete[] prm;
	
	
	
	
	
	
	
	
	
	
}
