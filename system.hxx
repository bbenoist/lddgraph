#ifndef system_HXX
#define system_HXX

#include <string>
#include <stdio.h>

using namespace std;

// Invokes a system command and returns its console output
static inline string system(const string & command)
{
  string coutput;
  FILE *cmd = popen(command.c_str(), "r");
  char result[24] = { 0x0 };
  while (fgets(result, sizeof(result), cmd) != NULL)
    coutput += result;
  pclose(cmd);
  return coutput;
}

#endif /* system_HXX */
