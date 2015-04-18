#pragma once

#include <utility>
#include <iostream>

template <class T> 
class ModArithmetic
{
public:
	ModArithmetic(T _value, T m);
	ModArithmetic(T m);
	virtual ~ModArithmetic();
	
	ModArithmetic<T>& operator+=(ModArithmetic<T> n);
	ModArithmetic<T>& operator-=(ModArithmetic<T> n);
	ModArithmetic<T>& operator*=(ModArithmetic<T> n);
	ModArithmetic<T>& operator/=(ModArithmetic<T> n);

	ModArithmetic<T> operator-(ModArithmetic<T> n) const;
	ModArithmetic<T> operator+(ModArithmetic<T> n) const;
	ModArithmetic<T> operator*(ModArithmetic<T> n) const;
	ModArithmetic<T> operator/(ModArithmetic<T> n) const;

	bool operator==(ModArithmetic<T> n);
	bool operator!=(ModArithmetic<T> n);
	
	T& getValue();
    void setValue(T v);

private:
	T value;
	T field_size;
};


template <typename T>
ModArithmetic<T>::ModArithmetic(T _value, T m) : field_size(m) 
{
	value=_value % field_size;
	if(value<0)
		value += field_size;
}

template <typename T>
ModArithmetic<T>::ModArithmetic(T m) : value(), field_size(m) 
{
}

template <typename T>
ModArithmetic<T>::~ModArithmetic()
{
}

template <typename T>
ModArithmetic<T>& ModArithmetic<T>::operator+=(ModArithmetic<T> n)
{
	value+=n.value;
	if(value>=field_size)
		value-=field_size;
	return *this;
}

template <typename T>
ModArithmetic<T>& ModArithmetic<T>::operator-=(ModArithmetic<T> n)
{
	if(n.value>value)
		value=value+field_size-n.value;
	else
		value-=n.value;
	return *this;
}

template <typename T>
ModArithmetic<T>& ModArithmetic<T>::operator*=(ModArithmetic<T> n)
{
	T x=value;
	T &y=n.value;
	value=0;

	//performing value=x+y
	while(n.value!=0)
	{
		if(y%2!=0)
		{
			value+=x;
			value%=field_size;
		}
		x+=x;
		x%=field_size;
		y/=2;
		//floor(y); //UNCLEAR
	}
	return *this;	
}

template <class T>
std::pair<T,T> euclid(T a, T b)
{
	if(a==0)
		return std::make_pair(0,1);
	if(b==0)
		return std::make_pair(1,0);
	std::pair<T,T> p=euclid(b, a%b);
	T y=p.first;
	T x=p.second;
	p.first=x;
	p.second=y-(a/b)*x;
	return p;
}

template <typename T>
ModArithmetic<T>& ModArithmetic<T>::operator/=(ModArithmetic<T> n)
{
	std::pair<T, T> p=euclid(field_size, n.value);
	if(p.first*field_size+p.second*n.value>1)
	{
		//gcd(field_size, n.value)!=1 => multiplicative inverse doesn't exist
		value=-1;
	}
	else
	{
		ModArithmetic<T> tmp(p.second, field_size);
		*this*=tmp;
	}
	return *this;	
}

template <typename T>
ModArithmetic<T> ModArithmetic<T>::operator-(ModArithmetic<T> n) const
{
	ModArithmetic<T> tmp(*this);
	return tmp-=n;
}

template <typename T>
ModArithmetic<T> ModArithmetic<T>::operator+(ModArithmetic<T> n) const
{
	return n+=*this;
}

template <typename T>
ModArithmetic<T> ModArithmetic<T>::operator*(ModArithmetic<T> n) const
{
	return n*=*this;
}

template <typename T>
ModArithmetic<T> ModArithmetic<T>::operator/(ModArithmetic<T> n) const
{
	ModArithmetic<T> tmp=*this;
	return tmp/=n;
}


template <typename T>
bool ModArithmetic<T>::operator==(ModArithmetic<T> n)
{
	return value==n.value && field_size==n.field_size;
}

template <typename T>
bool ModArithmetic<T>::operator!=(ModArithmetic<T> n)
{
	return value!=n.value || field_size!=n.field_size;
}

template <typename T>
T& ModArithmetic<T>::getValue()
{
	return value;
}

template <typename T>
void ModArithmetic<T>::setValue(T v)
{
	value=v;
}


