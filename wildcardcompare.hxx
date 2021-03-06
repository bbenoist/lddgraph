//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//                             lddgraph
// Small C++ tool which creates dependencies graphs of dynamically linked
// binaries using ldd and Graphviz.
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// This code is licensed under the terms specified in the LICENSE.BSD file
// https://github.com/bbenoist/lddgraph/blob/master/LICENSE.BSD
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#ifndef wildcardcompare_HXX
#define wildcardcompare_HXX
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#include <string>
#include <vector>
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

// Compares a string with a search term
static inline bool wildcardcompare(string searchterm, string checkagaints)
{
  bool found = false;
  vector < string > parts;
  string temp;
  if (searchterm == "*")
    return true;
  if (searchterm.size() - 1 > checkagaints.size())
    return false;
  string::const_iterator it = searchterm.begin(), end = searchterm.end();
  size_t counter = 0;
  while (it != end)
  {
    if (*it != '*')
      temp += *it;
    if (*it == '*')
    {
      parts.push_back(temp);
      temp = "";
    }
    it++;
  }
  parts.push_back(temp);
  vector<string>::const_iterator vectit = parts.begin(), vectend = parts.end();
  if (!parts[0].empty())
  {
    if (parts[0] != checkagaints.substr(0, parts[0].size()))
      return false;
  }
  else
    vectit++;
  size_t size = checkagaints.size();
  size_t pos = 0;
  size_t tempsize;
  while (vectit != vectend)
  {
    temp = *vectit;
    tempsize = temp.size();
    if (temp.empty())
      return true;
    while (pos + tempsize < size)
    {
      if (temp == checkagaints.substr(pos, temp.size()))
      {
        checkagaints.erase(0, pos + temp.size());
        found = true;
        break;
      }
      pos++;
    }
    if (found == false)
      return false;
    pos = 0;
    vectit++;
  }
  return true;
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

/// Compares a string with a list of search terms
static inline bool wildcardcontains(vector<string> vect, string checkagaints)
{
  vector<string>::const_iterator vectit = vect.begin(), vectend = vect.end();
  while (vectit != vectend)
  {
    if (wildcardcompare(*vectit, checkagaints))
      return true;
    vectit++;
  }
  return false;
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#endif /* wildcardcompare_HXX */
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
