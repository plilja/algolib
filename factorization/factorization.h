#include <vector>
#include <cmath>

/**
 * Finds the prime factors of a number. If one factor exists multiple times
 * in the factorization it will exists multiple times in the result.
 *
 * If the number is a prime number, only the number itself is returned.
 */
template<typename T>
std::vector<T> factorization(T num)
{
    std::vector<T> result;
    T remainder = num;
    while (remainder % 2 ==0) {
        result.push_back(2);
        remainder /= 2;
    }
    T possible_divisor = 3;
    while (remainder != 1) {
        T upper_lim = sqrt(remainder);
        for (; possible_divisor <= upper_lim; possible_divisor += 2) {
            if (remainder % possible_divisor == 0) {
                result.push_back(possible_divisor);
                remainder /= possible_divisor;
                break;
            }
        }
        if (possible_divisor > upper_lim) {
            if (remainder != 1) {
                result.push_back(remainder);
            }
            break;
        }
    }
    if (num == 1) {
        result.push_back(1);
    }
    return result;
}

