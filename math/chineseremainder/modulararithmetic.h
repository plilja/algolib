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
		T getValue() const;
		
		// Returns the number of possible values
		T getSize() const;
	
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
	if(size != rhs.getSize())
		assert(!"Can't use operator + with elements using different modulus. ");
	
	return Mod<T>(value + rhs.getValue(), size);
}

template <typename T>
const Mod<T> Mod<T>::operator - (const Mod<T> &rhs) const
{
	if(size != rhs.getSize())
		assert(!"Can't use operator - with elements using different modulus. ");
	
	if (rhs.getValue() > value) {
		return Mod<T>(value + size - rhs.getValue(), size);
	}
	
	else {
		return Mod<T>(value - rhs.getValue(), size);
	}
}

template <typename T>
const Mod<T> Mod<T>::operator * (const Mod<T> &rhs) const
{
	if(size != rhs.getSize())
		assert(!"Can't use operator * with elements using different modulus. ");
	
	T x = value;
	T y = rhs.getValue();
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
	if(size != rhs.getSize())
		assert(!"Can't use operator / with elements using different modulus. ");
	
	std::pair<T, T> p = euclid(size, rhs.getValue());
	
	if (p.first * size + p.second * rhs.getValue() > 1) {
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
	
	value = aux.getValue();
	size  = aux.getSize();
	
	return *this;
}

template <typename T>
Mod<T>& Mod<T>::operator -= (const Mod<T> &rhs)
{
	Mod<T> aux = *this - rhs;
	
	value = aux.getValue();
	size  = aux.getSize();
	
	return *this;
}

template <typename T>
Mod<T>& Mod<T>::operator *= (const Mod<T> &rhs)
{
	Mod<T> aux = *this * rhs;
	
	value = aux.getValue();
	size  = aux.getSize();
	
	return *this;
}

template <typename T>
Mod<T>& Mod<T>::operator /= (const Mod<T> &rhs)
{
	Mod<T> aux = *this / rhs;
	
	value = aux.getValue();
	size  = aux.getSize();
	
	return *this;
}

template <typename T>
bool Mod<T>::operator == (const Mod<T> &rhs) const
{
	if(size != rhs.getSize())
		assert(!"Can't compare elements using different modulus. ");
	return (value == rhs.getValue());
}

template <typename T>
bool Mod<T>::operator != (const Mod<T> &rhs) const
{
	return !(*this == rhs);
}

template <typename T>
T Mod<T>::getValue() const
{
	return value;
}

template <typename T>
T Mod<T>::getSize() const
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
