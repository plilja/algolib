#ifndef BIGNUM_H_
#define BIGNUM_H_

#include <vector>
#include <string>
#include <iostream>

typedef long long int lint; 

// number is stored in base 10^D
#define D 1

class BigNum
{
public:
	BigNum();

	BigNum(std::string sNumber);
	//BigNum(const BigNum &ref);
	virtual ~BigNum();
	
	//BigNum& operator=(const BigNum &ref);
	bool operator<(const BigNum &a) const;
	bool operator>(const BigNum &a) const;
	bool operator<=(const BigNum &a) const;
	bool operator>=(const BigNum &a) const;
	bool operator==(const BigNum &a) const;

	BigNum& operator/=(const BigNum &a);
	BigNum& operator+=(const BigNum &a);
	BigNum& operator-=(const BigNum &a);
	BigNum operator-(BigNum a) const;
	BigNum operator+(BigNum a) const;
	BigNum operator*(BigNum a) const;
	BigNum& operator*=(const BigNum &a);

	BigNum operator-() const;
	
	friend std::ostream& operator<<(std::ostream &os, const BigNum &a); 
private:
	std::vector<lint> number;
	mutable bool positive;
	//int m; //operations are performed modulo m 
};

#endif /*BIGNUM_H_*/
