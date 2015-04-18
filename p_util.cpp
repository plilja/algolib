#include <map>
#include <iostream>
#include <limits>
#include <vector>

/**
 * Get from a map with a default fallback value if the provided key isn't
 * present in the map.
 */
template <typename K, typename V>
V get_or_default(const  std::map <K, V> &m, const K &key, const V &defval)
{
    typename std::map<K, V>::const_iterator it = m.find(key);
    if (it == m.end()) {
        return defval;
    } else {
        return it->second;
    }
}

/**
 * Eat the rest of a line.
 */
template <typename CharType, typename CharTraits>
std::basic_istream <CharType, CharTraits> &
endl(std::basic_istream <CharType, CharTraits> &ins)
{
    return ins.ignore(std::numeric_limits <std::streamsize> ::max(), '\n');
}

std::vector<int> range(int from, int to) {
    std::vector<int> res;
    for (int i = from; i < to; ++i)
    {
        res.push_back(i);
    }
    return res;
}

std::vector<int> xrange(int to) {
    return range(0, to);
}


