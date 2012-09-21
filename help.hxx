//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//                             lddgraph
// Small C++ tool which creates dependencies graphs of dynamically linked
// binaries using ldd and Graphviz.
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// This code is licensed under the terms specified in the LICENSE.BSD file
// https://github.com/bbenoist/lddgraph/blob/master/LICENSE.BSD
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#ifndef help_HXX
#define help_HXX
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#include <iostream>
#include "config.h"
#include "progname.h"
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
using namespace std;
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

// Prints help on the console output
static inline void printhelp()
{
  cout << "Usage:" << endl;
  cout << "  " << program_name << " [options] file" << endl;
  cout << "Options:" << endl;
  cout << "  -i LIBRARY, --ignore=LIBRARY\tIgnore a specific library." << endl;
  cout << "  -I TEXT, --ignore-text=TEXT\tIgnore libraries when their path ";
  cout << "contains the text." << endl;
  cout << "  -e FILE, --image=FILE\t\tExport image file." << endl;
  cout << "  -f FORMAT, --image-format=FORMAT" << endl;
  cout << "\t\t\t\tOutput image format. ";
  cout << "Use 'dot -T?' for a complete list." << endl;
  cout << "  -g FILE, --graphviz\t\tExport Graphviz diagram." << endl;
  cout << "  -t, --trace-loaded-objects\tUse LD_TRACE_LOADED_OBJECTS ";
  cout << "instead of ldd." << endl;
  cout << "  -q, --quiet\t\t\tQuiet mode." << endl;
  cout << "  -V, --verbose\t\t\tVerbose mode." << endl;
  cout << "  -h, --help\t\t\tPrint this message and exit." << endl;
  cout << "  -v, --version\t\t\tPrint the version number of ";
  cout << program_name << " and exit." << endl;
  cout << endl << "lddgraph " << LDDGRAPH_VERSION << endl;
  cout << LDDGRAPH_COPYRIGHT << endl;
  cout << endl << "For bug reporting instructions, please see:" << endl;
  cout << "<https://github.com/bbenoist/lddgraph/issues>" << endl;
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#endif /* help_HXX */
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
