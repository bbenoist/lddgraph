#ifndef ldd_HXX
#define ldd_HXX

// Creates a graph of all the dependencies of a dynamically linked binary
void ldd(const string & file, vector<string> & libraries, bool useldd,
    bool verbose)
{
    string cmdResult;
    if (useldd)
    {
        cmdResult = system("ldd " + file);
    }
    else
    {
      setenv("LD_TRACE_LOADED_OBJECTS", "1", 1);
      cmdResult = system(file);
      unsetenv("LD_TRACE_LOADED_OBJECTS");
    }
    if (verbose)
        cout << cmdResult;
    istringstream cmdStream(cmdResult);
    string lddLine;
    while (std::getline(cmdStream, lddLine, '\n'))
    {
        if (contains(lddLine, "=>"))
            lddLine = lddLine.substr(lddLine.find_first_of('>') + 1);
        lddLine = lddLine.substr(0, lddLine.find_first_of('('));
        trim(lddLine);
        if (lddLine.size() > 0 && file != lddLine)
            libraries.push_back(trim(lddLine));
    }
}

// Recursively write dependencies
void lddRecurse(string file, vector<string> & alreadyScanned,
    vector<string> & ignoreList, ofstream & gvstream, bool useldd,
    bool quiet, bool verbose)
{
    if (!quiet)
      cout << "Scanning file " << file << endl;
    vector<string> libraries;
    ldd(file, libraries, useldd, verbose);
    alreadyScanned.push_back(file);
    for (int i = 0; i < libraries.size(); i++)
    {
        if (libraries[i].size() == 0
            || contains(ignoreList, libraries[i]))
            continue;
        gvstream << "\t\"" << file << "\" -> \"" << libraries[i] << "\""
            << endl;
        if (contains(alreadyScanned, libraries[i]))
            continue;
        lddRecurse(libraries[i], alreadyScanned,
            ignoreList, gvstream, useldd, quiet, verbose);
    }
}

#endif /* ldd_HXX */

