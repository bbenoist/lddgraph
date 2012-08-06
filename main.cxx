#include "lddgraph.hxx"
#include "help.hxx"

#include <string.h>

using namespace std;

// Entry point for lddgraph
int main (int argc, char* argv[])
{
  /* Prints output when no arguments where specified */
  if (argc < 2)
  {
    help();
    return 0;
  }

  lddgraph lddg(argv[argc - 1]);

  /*
   * Arguments parsing
   * Assuming that argv[0] is the executable path
   */
  for (int i = 1; i < argc - 1; i++)
  {
    int arglen = strlen(argv[i]);
    if (arglen < 2)
      arglen = 2;
    if (strncmp(argv[i], "-i", arglen) == 0)
    {
      i++;
      if (i < argc)
      {
        vector<string> ignorelist = lddg.getignorelist();
        string val = argv[i];
        ignorelist.push_back(trim(val));
        lddg.setignorelist(ignorelist);
      }
    }
    else if (strncmp(argv[i], "-e", arglen) == 0)
    {
      lddg.setimgmode(true);
      i++;
      if (i < argc)
        lddg.setimgoutput(argv[i]);
    }
    else if (strncmp(argv[i], "-f", arglen) == 0)
    {
      i++;
      if (i < argc)
        lddg.setimgformat(argv[i]);
    }
    else if (strncmp(argv[i], "-g", arglen) == 0)
    {
      lddg.setgvmode(true);
      i++;
      if (i < argc)
        lddg.setgvoutput(argv[i]);
    }
    else if(strncmp(argv[i], "-t", arglen) == 0)
    {
      lddg.setuseldd(false);
    }
    else if(strncmp(argv[i], "-q", arglen) == 0)
    {
      lddg.setquiet(true);
    }
    else if(strncmp(argv[i], "-v", arglen) == 0)
    {
      lddg.setverbose(true);
    }
    else // Invalid argument
    {
      if (!lddg.getquiet())
      {
        string err = "Error: Invalid argument ";
        perror((err + argv[i]).c_str());
      }
      return 0;
    }
  }

  lddg.run();

  return 0;
}

