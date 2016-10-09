#pragma once

#include "modulararithmetic.h"
#include "gcd.h"
#include <utility>
#include <vector>

/*
	Solves an equation of the form:
		x = a1 mod n1
		x = a2 mod n2
	
	Note: gcd(n1, n2) have to be = 1
*/
template<typename T>
std::pair<T, T> crt(const std::pair<T, T> &eq1, const std::pair<T, T> &eq2) {
    T N = eq1.second * eq2.second;

    // Calculate e1
    Mod<T> a1(eq1.first, N);
    Mod<T> M1(N / eq1.second, N);

    auto rs = extendedGcd(eq1.second, M1.getValue());

    Mod<T> e1(rs.b, N);

    // Calculate e2
    Mod<T> a2(eq2.first, N);
    Mod<T> M2(N / eq2.second, N);

    rs = extendedGcd(eq2.second, M2.getValue());

    Mod<T> e2(rs.b, N);

    // Calculate and return result
    auto res = (a1 * e1 * M1 + a2 * e2 * M2);
    return {res.getValue(), res.getSize()};
}

/*
    Solves an equation of the form:
        x = a1 mod n1
        x = a2 mod n2

    gcd(n1, n2) may be greater than 1. 

    If no solution exists {-1, -1} is returned.
*/
template<typename T>
std::pair<T, T> crtGeneral(const std::pair<T, T> &eq1, const std::pair<T, T> &eq2) {
    T common = gcd(eq1.second, eq2.second);

    Mod<T> a1_mod(eq1.first, common);
    Mod<T> a2_mod(eq2.first, common);

    // A solution exists iff a1 == a2 mod gcd(n1, n2)
    if (a1_mod != a2_mod) {
        return {-1, -1};
    } else if (common == std::min(eq1.second, eq2.second)) {
        return {std::max(eq1.first, eq2.first), std::max(eq1.second, eq2.second)};
    }

    T N = eq1.second * eq2.second / common;
    T n1_aux = eq1.second / common;

    // Compute e1
    Mod<T> M1(N / (common * n1_aux), N);
    auto rs1 = extendedGcd(n1_aux, M1.getValue());
    Mod<T> e1(rs1.b, N);

    T n2_aux = eq2.second / common;

    // Compute e2
    Mod<T> M2(N / (common * n2_aux), N);
    auto rs2 = extendedGcd(n2_aux, M2.getValue());
    Mod<T> e2(rs2.b, N);

    T a1_aux = eq1.first % eq1.second;
    T a2_aux = eq2.first % eq2.second;

    // Compute and return result
    auto res = Mod<T>(a1_aux, N) * e1 * M1 + Mod<T>(a2_aux, N) * e2 * M2;
    return {res.getValue(), res.getSize()};
}

/*
    Solves an equation of the form:
        x = a1 mod n1
        x = a2 mod n2
        ...
        x = am mod nm

    gcd(n1, n2, ..., nm) may be greater than 1.

    If no solution exists {-1, -1} is returned.
*/
template<typename T>
std::pair<T, T> crtGeneral(std::vector<std::pair<T, T> > &eqs) {
    if (eqs.size() == 0) {
        return {-1, -1};
    }
    if (eqs.size() == 1) {
        return eqs[0];
    }
    auto a = eqs.back();
    eqs.pop_back();
    auto b = eqs.back();
    eqs.pop_back();
    std::pair<T, T> eq1 = {a.first, a.second};
    std::pair<T, T> eq2 = {b.first, b.second};
    auto c = crtGeneral(eq1, eq2);
    if (c.first == -1 && c.second == -1) {
        return c;
    }
    eqs.push_back(c);
    return crtGeneral(eqs);
}

