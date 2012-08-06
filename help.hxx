#ifndef help_HXX
#define help_HXX

#include <iostream>

using namespace std;

// Prints help on the console output
void help()
{
    cout << "Usage:" << endl
        << "  lddgraph [options] file" << endl
        << "Options:" << endl
        << "  -i <library>\tIgnore a specific library." << endl
        << "  -I <text>\tIgnore libraries when their path contains the text."
        << endl
        << "  -e <file>\tExport image file." << endl
        << "  -f <format>\tOutput image format. Use 'dot -T?' for a"
        << " complete list." << endl
        << "  -g <file>\tExport Graphviz diagram." << endl
        << "  -t\t\tUse LD_TRACE_LOADED_OBJECTS instead of ldd." << endl
        << "  -q\t\tQuiet mode." << endl
        << "  -v\t\tVerbose mode." << endl
        << endl << "For bug reporting instructions, please see:" << endl
        << "https://github.com/bbenoist/lddgraph/issues" <<endl;
}

#endif /* help_HXX */

