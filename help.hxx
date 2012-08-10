#ifndef help_HXX
#define help_HXX

#include <iostream>

using namespace std;

// Prints help on the console output
void help()
{
  cout << "Usage:" << endl;
  cout << "  lddgraph [options] file" << endl;
  cout << "Options:" << endl;
  cout << "  -i <library>\tIgnore a specific library." << endl;
  cout << "  -I <text>\tIgnore libraries when their path contains the text."
      << endl;
  cout << "  -e <file>\tExport image file." << endl;
  cout << "  -f <format>\tOutput image format. Use 'dot -T?' for a complete"
      << " list." << endl;
  cout << "  -g <file>\tExport Graphviz diagram." << endl;
  cout << "  -t\t\tUse LD_TRACE_LOADED_OBJECTS instead of ldd." << endl;
  cout << "  -q\t\tQuiet mode." << endl;
  cout << "  -v\t\tVerbose mode." << endl;
  cout << endl << "For bug reporting instructions, please see:" << endl;
  cout << "https://github.com/bbenoist/lddgraph/issues" << endl;
}

#endif /* help_HXX */

