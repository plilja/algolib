/*
	Provides a data structure holding iformation about
	which numbers are prime and which aren't below a given 
	limit. 
*/

#pragma once

typedef unsigned int uint;

class PrimeSieve
{
	private:
		int *primes;
		uint nrOfPrimes;
		uint sieve_size;
	public:
		/*
		 * Construct a prime sieve of size n using
		 * the sieve of eratosthenes algorithm. 
		 * 
		 * Parameters:
		 * n : The size of the sieve (inclusive)
		 */
		PrimeSieve(uint n);
		
		/*
		 * Destructor.
		 */
		~PrimeSieve();
		
		/*
		 * The number of primes in the sieve. 
		 */
		int primes_in_sieve();
		
		/*
		 * Tells if n is a prime number.
		 * 
		 * Running time O(1) 
		 */
		bool isPrime(uint n) const;
};
