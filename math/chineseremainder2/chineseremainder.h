/*
	Martin Tittenberger
	Patrik Lilja
*/

#pragma once

#include "modulararithmetic.h"
#include <utility>

/*
	Solves an equation of the form:
		x = a1 mod n1
		x = a2 mod n2
	
	where <a1, n1> and <a2, n2> is the input to the function
	which returns the solution x mod N.
	
	Note: gcd(n1, n2) have to be = 1
*/
template <typename T>
Mod<T> crt(const std::pair<T, T> &eq1, const std::pair<T, T> &eq2)
{
	T N = eq1.second * eq2.second;
	
	// Calculate e1
	Mod<T> a1(eq1.first, N);
	Mod<T> M1(N / eq1.second, N);
	
	std::pair<T, T> rs = Mod<T>::euclid(eq1.second, M1.getValue());
	
	Mod<T> e1(rs.second, N);
	
	// Calculate e2
	Mod<T> a2(eq2.first, N);
	Mod<T> M2(N / eq2.second, N);
	
	rs = Mod<T>::euclid(eq2.second, M2.getValue());
	
	Mod<T> e2(rs.second, N);
	
	// Calculate and return result
	return (a1 * e1 * M1 + a2 * e2 * M2);
}
