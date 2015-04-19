#pragma once

#include <iostream>
#include <cassert>

/*
 * A class for modular arithmetic. 
 */
template <typename T>
class Mod
{
	public:
		/*
		 * Initialize a Mod object with value: 
		 * _value (mod _size).
		 *
		 * All operations on this class will be 
		 * performed (mod _size)
		 */
		Mod(T _value, T _size);
		
		const Mod<T> operator + (const Mod<T> &rhs) const;
		const Mod<T> operator - (const Mod<T> &rhs) const;
		const Mod<T> operator * (const Mod<T> &rhs) const;

		/*
		 * The operator / tries to find an element e such that
		 * e*rhs=*this. If no such element can be found, -1 is
		 * returned. 
		 */
		const Mod<T> operator / (const Mod<T> &rhs) const;
		
		Mod<T>& operator += (const Mod<T> &rhs);
		Mod<T>& operator -= (const Mod<T> &rhs);
		Mod<T>& operator *= (const Mod<T> &rhs);
		Mod<T>& operator /= (const Mod<T> &rhs);
		
		bool operator == (const Mod<T> &rhs) const;
		bool operator != (const Mod<T> &rhs) const;
		
		// Returns a pair, such that pair.first * a + pair.second * b = gcd(a, b)
		static std::pair<T, T> euclid(T a, T b);
		
		// Returns the current value
		T get_value() const;
		
		// Returns the number of possible values
		T get_size() const;
	
	private:
	 	T value, size;
};

template <typename T>
Mod<T>::Mod(T _value, T _size) : value(_value), size(_size)
{
	if(_size<=0)
		assert(!"The modulus used must be greater than 0");
	
	value %= size;
	
	if (value < 0) {
		value += size;
	}
}

template <typename T>
const Mod<T> Mod<T>::operator + (const Mod<T> &rhs) const
{
	if(size != rhs.get_size())
		assert(!"Can't use operator + with elements using different modulus. ");
	
	return Mod<T>(value + rhs.get_value(), size);
}

template <typename T>
const Mod<T> Mod<T>::operator - (const Mod<T> &rhs) const
{
	if(size != rhs.get_size())
		assert(!"Can't use operator - with elements using different modulus. ");
	
	if (rhs.get_value() > value) {
		return Mod<T>(value + size - rhs.get_value(), size);
	}
	
	else {
		return Mod<T>(value - rhs.get_value(), size);
	}
}

template <typename T>
const Mod<T> Mod<T>::operator * (const Mod<T> &rhs) const
{
	if(size != rhs.get_size())
		assert(!"Can't use operator * with elements using different modulus. ");
	
	T x = value;
	T y = rhs.get_value();
	T aux = 0;
	
	while (y != 0) {
		if ((y & 1) != 0) {
			aux += x;
			aux %= size;
		}
		
		x <<= 1;
		x %= size;
		y >>= 1;
	}
	
	return Mod<T>(aux, size);
}

template <typename T>
const Mod<T> Mod<T>::operator / (const Mod<T> &rhs) const
{
	if(size != rhs.get_size())
		assert(!"Can't use operator / with elements using different modulus. ");
	
	std::pair<T, T> p = euclid(size, rhs.get_value());
	
	if (p.first * size + p.second * rhs.get_value() > 1) {
		// Multiplicative inverse does not exist
		Mod<T> aux(-1, size);
		aux.value = -1;
		
		return aux;
	}
	
	else {
		return Mod<T>(value * p.second, size);
	}
}

template <typename T>
Mod<T>& Mod<T>::operator += (const Mod<T> &rhs)
{
	Mod<T> aux = *this + rhs;
	
	value = aux.get_value();
	size  = aux.get_size();
	
	return *this;
}

template <typename T>
Mod<T>& Mod<T>::operator -= (const Mod<T> &rhs)
{
	Mod<T> aux = *this - rhs;
	
	value = aux.get_value();
	size  = aux.get_size();
	
	return *this;
}

template <typename T>
Mod<T>& Mod<T>::operator *= (const Mod<T> &rhs)
{
	Mod<T> aux = *this * rhs;
	
	value = aux.get_value();
	size  = aux.get_size();
	
	return *this;
}

template <typename T>
Mod<T>& Mod<T>::operator /= (const Mod<T> &rhs)
{
	Mod<T> aux = *this / rhs;
	
	value = aux.get_value();
	size  = aux.get_size();
	
	return *this;
}

template <typename T>
bool Mod<T>::operator == (const Mod<T> &rhs) const
{
	if(size != rhs.get_size())
		assert(!"Can't compare elements using different modulus. ");
	return (value == rhs.get_value());
}

template <typename T>
bool Mod<T>::operator != (const Mod<T> &rhs) const
{
	return !(*this == rhs);
}

template <typename T>
T Mod<T>::get_value() const
{
	return value;
}

template <typename T>
T Mod<T>::get_size() const
{
	return size;
}

template <typename T>
std::pair<T, T> Mod<T>::euclid(T a, T b)
{
	if (a == 0) {
		return std::make_pair(0, 1);
	}
	
	if (b == 0) {
		return std::make_pair(1, 0);
	}
	
	std::pair<T, T> p = euclid(b, a % b);
	
	T y = p.first;
	T x = p.second;
	p.first = x;
	p.second = y - (a / b) * x;
	
	return p;
}
