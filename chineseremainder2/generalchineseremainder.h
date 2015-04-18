#pragma once

#include "modulararithmetic.h"
#include <utility>
#include <iostream>

using namespace std;

// Returns the greatest common divisor for "a" and "b"
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
	Solves an equation of the form:
		x = a1 mod n1
		x = a2 mod n2

	where <a1, n1> and <a2, n2> is the input to the function
	which returns the solution x mod N.
*/
template <typename T>
Mod<T> crt_general(const std::pair<T, T> &eq1, const std::pair<T, T> &eq2)
{
    T common = gcd(eq1.second, eq2.second);

    Mod<T> a1_mod(eq1.first, common);
    Mod<T> a2_mod(eq2.first, common);

    // A solution exists iff a1 == a2 mod gcd(n1, n2)
    if (a1_mod != a2_mod) {
        return Mod<T>(0, 1);
    }

    T N = eq1.second * eq2.second / common;
    T n1_aux = eq1.second / common;

    // Compute e1
    Mod<T> M1(N / (common * n1_aux), N);
    std::pair<T, T> rs = Mod<T>::euclid(n1_aux, M1.getValue());
    Mod<T> e1(rs.second, N);

    T n2_aux = eq2.second / common;

    // Compute e2
    Mod<T> M2(N / (common * n2_aux), N);
    rs = Mod<T>::euclid(n2_aux, M2.getValue());
    Mod<T> e2(rs.second, N);

    T a1_aux = eq1.first % eq1.second;
    T a2_aux = eq2.first % eq2.second;


    cerr<<a1_aux << " " << N << " " << e1.getValue() << " " << M1.getValue() << " "<<a2_aux << " "<<e2.getValue() << " "<<M2.getValue()<<endl;

    // Compute and return result
    return Mod<T>(a1_aux, N) * e1 * M1 + Mod<T>(a2_aux, N) * e2 * M2;
}
