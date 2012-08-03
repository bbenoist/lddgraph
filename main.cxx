#include <string.h>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include "trim.hxx"
#include "contains.hxx"
#include "system.hxx"
#include "ldd.hxx"

using namespace std;

// Entry point for lddgraph
int main (int argc, char* argv[])
{
    /* Prints output when no arguments where specified */
    if (argc < 2)
    {
        cout << "Usage:" << endl
            << "  lddgraph [OPTION...] file" << endl
            << "Options:" << endl
            << "  -f <format>\tOutput graph format 'dot -T?'"
            << " for a complete list." << endl
            << "  -o <file>\tOutput file." << endl
            << "  -i <library>\tIgnore a specific library."
            << endl
            << "  -v Verbose mode" << endl;
        return 0;
    }

    /* lddgraph options */
    string input = argv[argc - 1];
    string basename = input.substr(input.find_last_of('/') + 1);
    string output = basename + ".deps.gv";
    string format = "jpg";
    vector<string> ignoreList;
    bool verbose = false;

    /*
     * Arguments parsing
     * Assuming that argv[0] is the executable path
     */
    for (int i = 1; i < argc - 1; i++)
    {
        int arglen = strlen(argv[i]);
        if (arglen < 2)
            arglen = 2;
        if (strncmp(argv[i], "-f", arglen) == 0)
        {
            i++;
            if (i > argc)
                format = argv[i];
        }
        else if (strncmp(argv[i], "-o", arglen) == 0)
        {
            i++;
            if (i > argc)
                output = argv[i];
        }
        else if (strncmp(argv[i], "-i", arglen) == 0)
        {
            i++;
            if (i > argc)
                ignoreList.push_back(argv[i]);
        }
        else if(strncmp(argv[i], "-v", arglen) == 0)
        {
            verbose = true;
        }
        else
        {
            cout << "Error: Invalid parameter" << endl;
        }
    }

    ofstream graphStream;
    graphStream.open(output.c_str());
    if (!graphStream.is_open())
    {
        cout << "Error: Can't open file " << output << endl;
        return 0;
    }

    graphStream << "digraph Dependencies {" << endl;

    vector<string> alreadyScanned;

    lddRecurse(input, alreadyScanned, ignoreList, graphStream, verbose);

    graphStream << "}" << endl;
    graphStream.flush();
    graphStream.close();

    string dotCMD = "dot -T" + format + " -o" + basename + ".deps.jpg " + output;
    system(dotCMD);

    return 0;
}

