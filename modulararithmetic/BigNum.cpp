#include "BigNum.h"
#include "math.h"
#include <iostream>
#include <list>

using std::endl;
using std::cout;

namespace
{
	const uint ceiling=(uint) pow(10, D);
}

void removeLeadingZeros(std::vector<lint> &v)
{
    while(v.size()>1 && v[v.size()-1]==0)
    {
        v.erase(--v.end());
    }
}

BigNum::BigNum(std::string sNumber) : positive(true)
{
	if(sNumber.length()>0 && sNumber[0]=='-')
	{
		positive=false;
		sNumber=sNumber.substr(1, sNumber.length()-1);
	}
	//cout<<sNumber[0]<<endl;
	//uint limit=(uint) ceil((0.0+sNumber.length())/D);
	//cout<<"limit: "<<limit<<endl;
	for(int i=sNumber.length(); i>0; i-=D) 
	{
		int pos=i-D;
		int len=D;
		if(pos<0)
		{
			pos=0;
			len=sNumber.length()%D;
		}
		number.push_back(atoi(sNumber.substr(pos, len).c_str()));
		cout<<number[number.size()-1]<<endl;
	}
	//reverse(number.begin(), number.end());
	cout<<number.size()<<endl;
	cout<<"numbervek"<<endl;
	for(std::vector<lint>::iterator it=number.begin(); it!=number.end(); ++it)
		cout<<*it<<endl;
	cout<<"end numbervek"<<endl;
	removeLeadingZeros(number);
}

BigNum::~BigNum()
{
}

BigNum::BigNum()
{
}

BigNum& BigNum::operator+=(const BigNum &a)
{
	cout<<"plus: "<<*this<<" + "<<a<<endl;
	if(positive && !a.positive)
	{
		a.positive=true;
		*this-=a;
		a.positive=false;
		return *this;
	}
	if(!positive && a.positive)
	{
		cout<<"specialera:"<<endl;
		a.positive=true;
		positive=true;
		*this-=a;
		a.positive=true;
		positive=!positive;
		return *this;
	}
	int n1=number.size();
	int n2=a.number.size();
	lint tmp, carry=0, x, y;
	for(int i=0; i<std::max(n1, n2); ++i)
	{
		x=0;
		y=0;
		if(i<n1)
			x=number[i];
		else
			number.push_back(0);
		if(i<n2)
			y=a.number[i];
		tmp=x+y+carry;
		cout<<"tmp: "<<tmp<<" carry: "<<carry<<endl;
		tmp=tmp;
		number[i]=tmp % ceiling;
		if(number[i]<0)
			number[i] += ceiling;
		
		carry=tmp>=ceiling;
		std::cout<<"val:"<<number[i]<<" carr:  "<<carry<<" i:"<<i<<" x:"<<x<<" y:"<<y<<std::endl;
	}
	if(carry!=0)
		number.push_back(carry);
	
	return *this;
}

BigNum& BigNum::operator-=(const BigNum &a)
{
	cout<<"minus: "<<*this<<" - "<<a<<endl;
	if(!positive && !a.positive)
	{
		cout<<"apa"<<endl;
		positive=true;
		a.positive=true;
		*this-=a;
		positive=!positive;
		a.positive=false;
		return *this;
	}
	if(!positive)
	{
		positive=true;
		*this+=a;
		positive=false;
		return *this;
	}
	if(!a.positive)
	{
		cout<<"apor"<<endl;
		a.positive=true;
		*this+=a;
		a.positive=false;
		return *this;
	}
    if(a>*this)
    {
        BigNum tmp(a);
        tmp.positive=!tmp.positive;
        positive=!positive;
        tmp-=*this;
        number=tmp.number;
        return *this;
    }
	if(a>*this)
	{
		positive=false;
	}
	int n1=number.size();
	int n2=a.number.size();
	lint tmp, borrow=0, x, y;
	for(int i=0; i<std::max(n1, n2); ++i)
	{
		x=0;
		y=0;
		if(i<n1)
			x=number[i];
		else
			number.push_back(0);
		if(i<n2)
			y=a.number[i];
		tmp=x-y-borrow;
		cout<<"x: "<<x<<" y: "<<y<<" borr: "<<borrow<<" skriver; "<<number[i]<<" tmp: "<<tmp<<" ceil: "<<ceiling<<endl;
		borrow=tmp<0;
		//tmp=abs(tmp);
		number[i]=tmp % ceiling;
		if(number[i]<0)
			number[i] += ceiling;
	}
    removeLeadingZeros(number);
	cout<<"result: "<<*this<<endl;
	return *this;
}

BigNum BigNum::operator-(BigNum a) const
{
	if(a>*this)
	{
		BigNum ans=a-*this;
		ans.positive=!ans.positive;
		return ans;
	}
	uint n=std::max(number.size(), a.number.size());
	lint borrow=0;
	BigNum ans("0");
	for(uint i=0; i<n; ++i)
		ans.number.push_back(0);
	int x, y;
	for(uint i=0; i<n; ++i)
	{
		x=0; y=0;
		if(i<number.size())
			x=number[i];
		if(i<a.number.size())
			y=a.number[i];
			
		//cout<<"x: "<<x<<" y: "<<y<<" borrow: "<<borrow<<endl;
		lint tmp=x-y-borrow;
		ans.number[i]=tmp % ceiling;
		if(ans.number[i]<0)
			ans.number[i]+=ceiling;
		borrow = tmp<0;
	}
	if(borrow==1)
		ans.positive=false;
    removeLeadingZeros(ans.number);
	//cout<<ans<<endl;
	return ans;
	/*a.positive=!a.positive;
	positive=!positive;
	BigNum res = a-=*this;
	a.positive=!a.positive;
	positive=!positive;
	return res;*/
}

BigNum BigNum::operator+(BigNum a) const
{
	return a+=*this;
}

BigNum BigNum::operator*(BigNum a) const
{
	uint n1=number.size();
	uint n2=a.number.size();
	BigNum res("0");
	lint x,y;
	while(res.number.size()<n1+n2+1)
		res.number.push_back(0);
	for(uint i=0; i<n1; ++i)
	{
		for(uint j=0; j<n2; ++j)
		{
			if(i<number.size())
				x=number[i];
			if(j<a.number.size())
				y=a.number[j];
			res.number[i+j]=res.number[i+j]+x*y;
		}
		lint carry=0;
		for(uint j=0; j<n1+n2; ++j)
		{
			res.number[j] += carry;
			lint tmp=res.number[j]/ceiling;
			//carry=(res[j]-(res[j]%ceiling))/ceiling;
			res.number[j] %= ceiling;
			if(res.number[j]<0)
				res.number[j]+=ceiling;
			carry=tmp;
		}
		res.number[n1+n2]=carry;
	}
	removeLeadingZeros(res.number);
	if((positive && a.positive) || (!positive && !a.positive))
		positive=true;
	else
		positive=false;
	return res;

//	return a*=*this;
}

BigNum& BigNum::operator*=(const BigNum &a)
{	
	uint n1=number.size();
	uint n2=a.number.size();
	std::vector<lint> res;
	while(res.size()<n1+n2+1)
		res.push_back(0);
	for(uint i=0; i<n1; ++i)
	{
		for(uint j=0; j<n2; ++j)
		{
			res[i+j]=res[i+j]+number[i]*a.number[j];
		}
		lint carry=0;
		for(uint j=0; j<n1+n2; ++j)
		{
			res[j] += carry;
			carry=(res[j]-(res[j]%ceiling))/ceiling;
			res[j] %= ceiling;
		}
	}
	number=res;
	removeLeadingZeros(number);
	if((positive && a.positive) || (!positive && !a.positive))
		positive=true;
	else
		positive=false;
	return *this;
}

BigNum& BigNum::operator/=(const BigNum &a)
{
	
	
}


BigNum BigNum::operator-() const
{
	BigNum n(*this);
	n.positive=!positive;
	return n;
}


std::ostream& operator<<(std::ostream &os, const BigNum &a)
{
	bool first=true;
	if(!a.positive)
		os<<"-";
	for(std::vector<lint>::const_reverse_iterator it=a.number.rbegin(); it!=a.number.rend(); ++it)
	{
		if(!first)
		{
			int i=D-1;
			while(*it<pow(10, i) && i>0)
			{
				os<<"0";
				--i;
			}
		}
		os<<*it;
		first=false;
	}
	return os;
} 

bool BigNum::operator<(const BigNum &a) const
{
	if(operator==(a))
		return false;
	if(positive && !a.positive)
		return false;
	if(!positive && a.positive)
		return true;
	if(number.size()>a.number.size())
	{
		return false;
	}
	if(number.size()<a.number.size())
	{
		return true;
	}
	//equal size number vector
	for(uint i=number.size()-1; i>=0; --i)
	{
		if(number[i]<a.number[i])
			return true;
		if(number[i]>a.number[i])
			return false;
	}
	return false; 	
}

bool BigNum::operator>(const BigNum &a) const
{
	if(operator==(a))
	{
		return false;
	}
	return !operator<(a);
}

bool BigNum::operator<=(const BigNum &a) const
{
	if(operator==(a))
		return true;
	return operator<(a);
}

bool BigNum::operator>=(const BigNum &a) const
{
	if(operator==(a))
		return true;
	return !operator<(a);
}

bool BigNum::operator==(const BigNum &a) const
{
	if(positive!=a.positive)
	{
		//they have different sign
		if(number.size()>1 || a.number.size()>1)
			return false;
		if(number.size()==1 && number[0]!=0)
			return false;
		if(a.number.size()==1 && a.number[0]!=0)
			return false;
		return true;
	}
	if(number.size()!=a.number.size())
		return false;
	for(uint i=0; i<number.size(); ++i)
	{
		if(number[i]!=a.number[i])
			return false;
	}
	return true;
}

