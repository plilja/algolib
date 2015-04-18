#include <cassert>
#include <iostream>
#pragma once

template<typename T>
class Rational
{
	private:
		T n, d; // Numerator, Denominator
		
		T gcd(T a, T b) const;
		T lcm(T a, T b) const;
	
	public:
		Rational(T numerator, T denominator);
		
		Rational<T> operator + (const Rational &rhs) const;
		Rational<T> operator - (const Rational &rhs) const;
		Rational<T> operator * (const Rational &rhs) const;
		Rational<T> operator / (const Rational &rhs) const;
		
		bool operator == (const Rational &rhs) const;
		bool operator != (const Rational &rhs) const;
		
		T num() const;
		T den() const;
};

template <typename T>
Rational<T>::Rational(T num, T den) : n(num), d(den)
{
	// Normalize
	T aux = gcd(n, d);
	
	n /= aux;
	d /= aux;
	
	// a / -b => -a / b, -a / -b => a / b
	if (d < 0) {
		n = -n;
		d = -d;
	}
    if(d==0)
    {
        if(n>0)
            n=1;
        if(n<0)
            n=-1;
    }
    if(n==0 && d!=0)
        d=1;
        
    
}

template <typename T>
Rational<T> Rational<T>::operator + (const Rational<T> &rhs) const
{
    if(d==0 && rhs.den()==0)
    {
        if(n==0 || rhs.num()==0)
            return Rational<T>(0, 0);
        if(n==1 && rhs.num()==1)
            return Rational<T>(1, 0);
        if(n==-1 && rhs.num()==-1)
            return Rational<T>(-1, 0);
        return Rational<T>(0, 0);
    }
    if(d==0)
    {
        if(n==0)
            return Rational<T>(0,0);
        return *this;
    }
    if(rhs.den()==0)
    {
        if(rhs.num()==0)
            return Rational<T>(0,0);
        return rhs;
    }
    return Rational<T>(n*rhs.den()+rhs.num()*d, d*rhs.den());
}

template <typename T>
Rational<T> Rational<T>::operator - (const Rational<T> &rhs) const
{
	return *this + Rational(-rhs.num(), rhs.den());
}

template <typename T>
Rational<T> Rational<T>::operator * (const Rational<T> &rhs) const
{
    if((d==0 && n==0) || (rhs.den()==0 && rhs.num()==0))
        return Rational<T>(0,0);
    if(d==0)
    {
        if(rhs.num()==0 && rhs.den()!=0)
        {
            return Rational<T>(0, 1);
        }
    }
    if(rhs.den()==0)
    {
        if(n==0 && d!=0)
        {
            return Rational<T>(0, 1);
        }
    }
	return Rational<T>(n * rhs.num(), d * rhs.den());
}

template <typename T>
Rational<T> Rational<T>::operator / (const Rational<T> &rhs) const
{
	return Rational<T>(n * rhs.den(), d * rhs.num());
}

template <typename T>
bool Rational<T>::operator == (const Rational<T> &rhs) const
{
	return (n == rhs.num() && d == rhs.den());
}

template <typename T>
bool Rational<T>::operator != (const Rational<T> &rhs) const
{
	return !(*this == rhs);
}

template <typename T>
T Rational<T>::gcd(T a, T b) const
{
	if (a == 0 || b == 0) {
		return 1;
	}
	
	while (true) {
		a %= b;
		
		if (a == 0) {
			return b;
		}
		
		b %= a;
		
		if (b == 0) {
			return a;
		}
	}
}

template <typename T>
T Rational<T>::lcm(T a, T b) const
{
	return (a * b) / gcd(a, b);
}

template <typename T>
T Rational<T>::num() const
{
	return n;
}

template <typename T>
T Rational<T>::den() const
{
	return d;
}
