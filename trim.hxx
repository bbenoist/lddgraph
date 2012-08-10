#ifndef trim_HXX
#define trim_HXX

#include <algorithm>
#include <string>

using namespace std;

// trim from start
static inline string & ltrim(string & s)
{
  s.erase(s.begin(),
      find_if(s.begin(), s.end(), not1(ptr_fun<int, int>(isspace))));
  return s;
}

// trim from end
static inline string & rtrim(string & s)
{
  s.erase(
      find_if(s.rbegin(), s.rend(), not1(ptr_fun<int, int>(std::isspace))).base(),
      s.end());
  return s;
}

// trim from both ends
static inline string & trim(string & s)
{
  return ltrim(rtrim(s));
}

#endif /* trim_HXX */

