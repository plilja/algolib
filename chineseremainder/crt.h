/*
 * Author: Patrik Lilja
 * Group: Patrik Lilja, Martin Tittenberger
 */
#ifndef CRT_H_
#define CRT_H_

#include <iostream>
//#include <iterator>
#include <utility>
#include <list>
#include "ModArithmetic.h"

using std::cout;
using std::endl;

/*
 * Solve the system of equations using the chinese remainder
 * theorem.
 * 
 * The system is of the form:
 * a1=x mod n1
 * a2=x mod n2
 * ...
 * ak=x mod nk
 * 
 * Parameters:
 * equations: The description of the equations. The i:th pair equals pair(a_i, n_i).
 * 
 * Returns: A pair p(x, M), where x is the solution to the system of equations and
 * 			M is the product of all n:s. 
 * 
 * Note that The template type T should have the characteristics of an integer type.  
 */
template <typename T>
std::pair<T, T> crt(std::list<std::pair<T, T> > equations);

namespace //anonymous
{
	/*
	 * 
	 */
	/**template <class T>
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
        }*/

    template <typename T>
    T gcd(T a, T b)
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
    

	/*
	 * Chinese remainder theorem helper function. 
	 * 
	 * Parameters: 
	 * N: this should equal the product over the primes in the equations.
	 * equations: the equations
	 * 
	 * Returns: the solution x to the equations
	 */
	template <typename T>
	T _crt(const T &N, std::list<std::pair<T, T> > &equations)
	{
		if(equations.empty())
			return 0;
		T tmp=equations.front().first;
		ModArithmetic<T> ai(tmp, N);
		T ni=equations.front().second;
		equations.pop_front();
		tmp=N/ni;
		cout<<tmp<<endl;
		ModArithmetic<T> N_remainder(tmp, N);
		std::pair<T, T> p=euclid(ni, N_remainder.getValue());
		ModArithmetic<T> e(p.second, N);
		ModArithmetic<T> res(_crt<T>(N, equations), N);
		res=res+ai*e*N_remainder;
		cout<<"Sol for: "<<ai.getValue()<<" is: "<<res.getValue()<<" N_rem: "<<N_remainder.getValue()<<" e: "<<e.getValue()<<" mod: "<<N<<endl;
		return res.getValue();
	}
}

template <typename T>
std::pair<T, T> crt(std::list<std::pair<T, T> > equations)
{
	T N=1;
	for(typename std::list<std::pair<T, T> >::iterator it=equations.begin(); it!=equations.end(); ++it)
	{
		N *= it->second;
	}
	return std::make_pair(_crt<T>(N, equations), N);
}

template <typename T>
std::pair<T, T> crtplus2(T a1, T n1, T a2, T n2)
{
    T common=gcd(n1, n2);
    ModArithmetic<T> n1_reduced(n1, common);
    ModArithmetic<T> n2_reduced(n2, common);

    //A solution only exists if
    //n1==n2 mod gcd(n1,n2)
    if(n1_reduced!=n2_reduced) 
    {
    	return std::make_pair(-1, -1);
    }
    
    //Guard against equations of the type
    //x==0 mod 2
    //x==1 mod 2
    if(n1==n2)
    {
	    ModArithmetic<T> a1_reduced(a1, n1);
	    ModArithmetic<T> a2_reduced(a2, n1);
    	
        if(a1_reduced==a2_reduced)
            return std::make_pair(a1_reduced.getValue(), n1);
        else
            return std::make_pair(-1,-1);
    }
    
    T N=n1*n2/common;
    std::list<std::pair<T, T> > equations;
    cout<<"before: "<<n1<<endl;
    //n1/=common;
    cout<<"after: "<<n1<<endl;
    //n2/=common;
    equations.push_front(std::make_pair(a1, n1));
    equations.push_front(std::make_pair(a2, n2));
    return std::make_pair(_crt(N,equations), N);
}

template <typename T>
std::pair<T, T> crtplus(T a1, T n1, T a2, T n2)
{
    T common=gcd(n1, n2);
    
    ModArithmetic<T> a1_reduced(a1, common);
    ModArithmetic<T> a2_reduced(a2, common);

    //A solution exists if and only if
    //a1==a2 mod gcd(n1,n2)
    if(a1_reduced!=a2_reduced) 
    {
    	return std::make_pair(-1, -1);
    }
    
    //Guard against equations of the type
    //x==0 mod 2
    //x==1 mod 2
    /*if(n1==n2)
    {
	    ModArithmetic<T> a1_reduced(a1, n1);
	    ModArithmetic<T> a2_reduced(a2, n1);
    	
        if(a1_reduced==a2_reduced)
            return std::make_pair(a1_reduced.getValue(), n1);
        else
            return std::make_pair(-1,-1);
    }*/
    T N=n1*n2/common;
    a1%=n1;
    a2%=n2;
    n1/=common;
    n2/=common;

	T tmp=N/(common*n1);
	ModArithmetic<T> N1_remainder(tmp, N);
	std::pair<T, T> p=euclid(n1, N1_remainder.getValue());
	ModArithmetic<T> e1(p.second, N);
    ModArithmetic<T> _a1(a1, N);
    //cout<<"a1: "<<_a1.getValue()<<" e1: "<<e1.getValue()<<" n1remainder; "<<N1_remainder.getValue()<<endl; 
	ModArithmetic<T> res=_a1*e1*N1_remainder;
    //cout<<"debug: "<<res.getValue()<<endl;

	tmp=N/(common*n2);
	ModArithmetic<T> N2_remainder(tmp, N);
	p=euclid(n2, N2_remainder.getValue());
	ModArithmetic<T> e2(p.second, N);
    ModArithmetic<T> _a2(a2, N);
    //cout<<"a1: "<<_a1.getValue()<<" e1: "<<e1.getValue()<<" n1remainder; "<<N1_remainder.getValue()<<endl; 
	ModArithmetic<T> t=_a2*e2*N2_remainder;
    //cout<<"debug: "<<t.getValue()<<endl;
    res+=t;


	return std::make_pair(res.getValue(), N);
}



#endif /*CRT_H_*/
