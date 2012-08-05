#include <string.h>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdlib.h>
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
            << "  lddgraph [options] file" << endl
            << "Options:" << endl
            << "  -i <library>\tIgnore a specific library." << endl
            << "  -e <file>\tExport image file." << endl
            << "  -f <format>\tOutput image format. Use 'dot -T?' for a"
            << " complete list." << endl
            << "  -g <file>\tExport Graphviz diagram." << endl
            << "  -t\t\tUse LD_TRACE_LOADED_OBJECTS instead of ldd." << endl
            << "  -q\t\tQuiet mode." << endl
            << "  -v\t\tVerbose mode." << endl
            << endl << "For bug reporting instructions, please see:" << endl
            << "https://github.com/bbenoist/lddgraph/issues" <<endl;
        return 0;
    }

    /* lddgraph options */
    string input = argv[argc - 1];
    string basename = input.substr(input.find_last_of('/') + 1);
    string gvoutput = basename + ".deps.gv";
    string imgoutput = basename + ".deps.jpg";
    string format = "jpg";
    vector<string> ignoreList;
    bool gvmode = false;
    bool imgmode = false;
    bool useldd = true;
    bool quiet = false;
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
        if (strncmp(argv[i], "-i", arglen) == 0)
        {
            i++;
            if (i > argc)
                ignoreList.push_back(argv[i]);
        }
        else if (strncmp(argv[i], "-e", arglen) == 0)
        {
            imgmode = true;
            i++;
            if (i > argc)
                imgoutput = argv[i];
        }
        else if (strncmp(argv[i], "-f", arglen) == 0)
        {
            i++;
            if (i > argc)
                format = argv[i];
        }
        else if (strncmp(argv[i], "-g", arglen) == 0)
        {
            gvmode = true;
            i++;
            if (i > argc)
                gvoutput = argv[i];
        }
        else if(strncmp(argv[i], "-t", arglen) == 0)
        {
            useldd = false;
        }
        else if(strncmp(argv[i], "-q", arglen) == 0)
        {
            quiet = true;
        }
        else if(strncmp(argv[i], "-v", arglen) == 0)
        {
            verbose = true;
        }
        else // Invalid argument
        {
            if (!quiet)
            {
                string err = "Error: Invalid argument ";
                perror((err + argv[i]).c_str());
            }
            return 0;
        }
    }
    if (quiet && verbose)
    {
        perror("Incompatible options -s and -v, please choose one.");
        return 0;
    }

    if (!quiet)
        cout << "Generating graph" << endl;
    if (verbose)
        cout << "Writing file " << gvoutput << endl;
    ofstream gvstream;
    gvstream.open(gvoutput.c_str());
    if (!gvstream.is_open())
    {
        if (!quiet)
            perror(("Error: Unable to open file " + gvoutput).c_str());
        return 0;
    }

    gvstream << "digraph Dependencies {" << endl;

    /* Invokes ldd recursively */
    vector<string> alreadyScanned;
    lddRecurse(input, alreadyScanned, ignoreList, gvstream, useldd, quiet,
        verbose);

    gvstream << "}" << endl;
    gvstream.flush();
    gvstream.close();

    /* Graphviz mode */
    if (gvmode && !imgmode)
        return 0;

    /* Image file generation */
    if (verbose)
        cout << "Writing file " << imgoutput << endl;
    string dotcmd = "dot -T" + format + " -o" + imgoutput + " " + gvoutput;
    system(dotcmd.c_str());

    /* Graphviz file cleanup */
    if (verbose)
        cout << "Deleting file " << gvoutput << endl;
    if (!gvmode && remove(gvoutput.c_str()) != 0 && !quiet)
        perror(("Error: Unable to delete file " + gvoutput).c_str());

    /* Image mode */
    if (imgmode)
        return 0;

    /* Image file display */
    string dispcmd = "display " + imgoutput;
    system(dispcmd.c_str());

    /* Image file cleanup */
    if (verbose)
        cout << "Deleting file " << imgoutput << endl;
    if (remove(imgoutput.c_str()) != 0 && !quiet)
        perror(("Error: Unable to delete file " + imgoutput).c_str());

    return 0;
}

