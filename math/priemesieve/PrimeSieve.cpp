#include "PrimeSieve.h"
#include <math.h>
#include <cassert>

namespace 
{
	bool primes_counted=false;
	static const unsigned char BitsSetTable256[] = 
	{
	  0, 1, 1, 2, 1, 2, 2, 3, 1, 2, 2, 3, 2, 3, 3, 4, 
	  1, 2, 2, 3, 2, 3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 5, 
	  1, 2, 2, 3, 2, 3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 5, 
	  2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6, 
	  1, 2, 2, 3, 2, 3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 5, 
	  2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6, 
	  2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6, 
	  3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7, 
	  1, 2, 2, 3, 2, 3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 5, 
	  2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6, 
	  2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6, 
	  3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7, 
	  2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6, 
	  3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7, 
	  3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7, 
	  4, 5, 5, 6, 5, 6, 6, 7, 5, 6, 6, 7, 6, 7, 7, 8
	};
}
			
PrimeSieve::PrimeSieve(uint n) : nrOfPrimes(-1), sieve_size(n)
{
	uint n_half=n/2+1;
	primes=new int[n_half/32+1];
	
	for(uint i=0; i<n_half/32+1; ++i)
	{
		primes[i]=0xFFFFFFFF;
	}
	//memset(primes, 0xFFFFFFFF, 4*(n_half/32+1));
	uint n_half_sqrt=(int) sqrt(n_half)+1;
	uint p, i, j;
	for (i = 1; i <= n_half_sqrt; ++i) {
		if((primes[i>>5] & (1<<(i&31))) != 0) {
			p=i+i+1; //p is prime
			for (j = (p*p)/2; j <= n_half; j += p) {
				primes[j>>5] &=~(1<<(j&31));
			}
		}
	}
}

PrimeSieve::~PrimeSieve()
{
	delete[] primes;
}

bool PrimeSieve::isPrime(uint n) const
{
	if (n <= 1) {
		return false;
	}
	
	else if (n == 2) {
		return true;
	}
	
	else {
		if ((n & 1) == 0) { 
			return false;
		}
		n=n>>1;
		return (primes[n>>5] & (1<<(n&31))) != 0;
	}
}

int PrimeSieve::primes_in_sieve()
{
	if(!primes_counted)
	{
		nrOfPrimes=0;
		uint limit=(sieve_size/2)>>5;
		
		uint v;
		//perform a bit count on the primes vector
		for(uint i=0; i<limit; ++i)
		{
			v=primes[i];
			nrOfPrimes += BitsSetTable256[v & 0xff] + 
    						BitsSetTable256[(v >> 8) & 0xff] + 
    						BitsSetTable256[(v >> 16) & 0xff] + 
    						BitsSetTable256[v >> 24]; 			
		}
		v=primes[limit];
		uint high_bit=(sieve_size>>1)&31;
		for(uint i=0; i<=high_bit; ++i)
		{
			nrOfPrimes += v & 1;
			v = v>>1;
		}
		primes_counted=true;
	}
	return nrOfPrimes;
}

