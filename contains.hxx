#ifndef contains_HXX
#define contains_HXX

#include <vector>
#include <string>

using namespace std;

template <typename T>

// Returns true if a vector contains the specified value
static inline bool contains(const vector<T> & vect, const T & val)
{
  return (find(vect.begin(), vect.end(), val) != vect.end());
}

// Returns true if a string contains the specified string element
static inline bool contains(string str, string element)
{
  return string::npos != str.find(element);
}

#endif /* contains_HXX */

