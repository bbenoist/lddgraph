#ifndef ldd_HXX
#define ldd_HXX

// Creates a graph of all the dependencies of a dynamically linked binary
void ldd(const string & file, vector<string> & libraries, bool verbose)
{
    cout << "Info: Scanning file " << file << endl;
    string cmdResult = system("ldd " + file);
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
        if (lddLine.size() > 0)
            libraries.push_back(trim(lddLine));
    }
}

// Recursively write dependencies
void lddRecurse(string file, vector<string> & alreadyScanned,
    vector<string> & ignoreList, ofstream & graphStream, bool verbose)
{
    vector<string> libraries;
    ldd(file, libraries, verbose);
    for (int i = 0; i < libraries.size(); i++)
    {
        if (libraries[i].size() == 0
            || contains(ignoreList, libraries[i]))
            continue;
        graphStream << "\t\"" << file << "\" -> \"" << libraries[i] << "\""
            << endl;
        if (contains(alreadyScanned, libraries[i]))
            continue;
        lddRecurse(libraries[i], alreadyScanned,
            ignoreList, graphStream, verbose);
        alreadyScanned.push_back(libraries[i]);
    }
}

#endif /* ldd_HXX */

