#ifndef lddgraph_HXX
#define lddgraph_HXX

#include "trim.hxx"
#include "contains.hxx"
#include "system.hxx"

#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

// lddgraph main class
class lddgraph
{
  private:
    string _input; // Input binary file
    bool _imgmode; // Image export mode
    string _imgoutput; // Output image file
    string _imgformat; // Output image file format
    bool _gvmode; // Graphviz export mode
    string _gvoutput; // Graphviz output file
    bool _useldd; // True to use ldd instead of LD_TRACE_LOADED_OBJECTS
    bool _quiet; // True to only display error messages
    bool _verbose; // Displays every information available
    vector<string> _ignorelist; // List of libraries to ignore

  public:
    lddgraph(string input)
    {
      _input = input;
      string basename = input.substr(input.find_last_of('/') + 1);
      _gvoutput = basename + ".deps.gv";
      _imgoutput = basename + ".deps.jpg";
      _imgformat = "jpg";
      _gvmode = false;
      _imgmode = false;
      _useldd = true;
      _quiet = false;
      _verbose = false;
    }

    const string & getinput()
    {
      return _input;
    }

    void setinput(const string & input)
    {
      _input = input;
    }

    const vector<string> & getignorelist()
    {
      return _ignorelist;
    }

    void setignorelist(vector<string> ignorelist)
    {
      _ignorelist = ignorelist;
    }

    bool getimgmode()
    {
      return _imgmode;
    }

    void setimgmode(bool imgmode)
    {
      _imgmode = imgmode;
    }

    const string & getimgoutput()
    {
      return _imgoutput;
    }

    void setimgoutput(const string & imgoutput)
    {
      _imgoutput = imgoutput;
    }

    const string & getimgformat()
    {
      return _imgformat;
    }

    void setimgformat(const string & imgformat)
    {
      _imgformat = imgformat;
    }

    bool getgvmode()
    {
      return _gvmode;
    }

    void setgvmode(bool gvmode)
    {
      _gvmode = gvmode;
    }

    const string & getgvoutput()
    {
      return _gvoutput;
    }

    void setgvoutput(const string & gvoutput)
    {
      _gvoutput = gvoutput;
    }

    bool getuseldd()
    {
      return _useldd;
    }

    void setuseldd(bool useldd)
    {
      _useldd = useldd;
    }

    bool getquiet()
    {
      return _quiet;
    }

    void setquiet(bool quiet)
    {
      _quiet = quiet;
    }

    bool getverbose()
    {
      return _verbose;
    }

    void setverbose(bool verbose)
    {
      _verbose = verbose;
    }

  private:
    // Removes the specified file and returns true if succeed
    bool removefile(const string & file)
    {
      if (remove(file.c_str()) != 0)
      {
        if (!_quiet)
          perror(("Error: Unable to delete file " + file).c_str());
        return false;
      }
      return true;
    }

    // Recursively write dependencies
    void lddrecurse(string file, vector<string> & alreadyscanned,
                    ofstream & gvstream)
    {
      if (!_quiet)
        cout << "Scanning file " << file << endl;
      vector<string> libraries;
      ldd(file, libraries);
      alreadyscanned.push_back(file);
      for (int i = 0; i < libraries.size(); i++)
      {
        if (libraries[i].size() == 0
            || contains(_ignorelist, libraries[i]))
          continue;
        gvstream << "\t\"" << file << "\" -> \"" << libraries[i] << "\""
          << endl;
        if (contains(alreadyscanned, libraries[i]))
          continue;
        lddrecurse(libraries[i], alreadyscanned, gvstream);
      }
    }

    // Creates a graph of all the dependencies of a dynamically linked binary
    void ldd(const string & file, vector<string> & libraries)
    {
      string cmdresult;
      if (_useldd)
      {
        cmdresult = system("ldd " + file);
      }
      else
      {
        setenv("LD_TRACE_LOADED_OBJECTS", "1", 1);
        cmdresult = system(file);
        unsetenv("LD_TRACE_LOADED_OBJECTS");
      }
      if (_verbose)
        cout << cmdresult;
      istringstream cmdstream(cmdresult);
      string lddline;
      while (std::getline(cmdstream, lddline, '\n'))
      {
        if (contains(lddline, "=>"))
          lddline = lddline.substr(lddline.find_first_of('>') + 1);
        lddline = lddline.substr(0, lddline.find_first_of('('));
        trim(lddline);
        if (lddline.size() > 0 && file != lddline)
          libraries.push_back(trim(lddline));
      }
    }

  public:
    // Begin of the lddgraph process
    bool run()
    {
      if (_quiet && _verbose)
      {
        perror("Incompatible options -s and -v, please choose one.");
        return 0;
      }

      if (!_quiet)
        cout << "Generating graph" << endl;
      if (_verbose)
        cout << "Writing file " << _gvoutput << endl;
      ofstream gvstream;
      gvstream.open(_gvoutput.c_str());
      if (!gvstream.is_open())
      {
        if (!_quiet)
          perror(("Error: Unable to open file " + _gvoutput).c_str());
        return false;
      }

      gvstream << "digraph Dependencies {" << endl;

      /* Invokes ldd recursively */
      vector<string> alreadyScanned;
      lddrecurse(_input, alreadyScanned, gvstream);

      gvstream << "}" << endl;
      gvstream.flush();
      gvstream.close();

      /* Graphviz mode */
      if (_gvmode && !_imgmode)
        return true;

      /* Image file generation */
      if (_verbose)
        cout << "Writing file " << _imgoutput << endl;
      string dotcmd = "dot ";
      dotcmd += "-T" + _imgformat + " -o" + _imgoutput + " " + _gvoutput;
      system(dotcmd.c_str());

      /* Graphviz file cleanup */
      if (_verbose)
        cout << "Deleting file " << _gvoutput << endl;
      if (!_gvmode && !removefile(_gvoutput))
        return false;

      /* Image mode */
      if (_imgmode)
        return true;

      /* Image file display */
      string dispcmd = "display " + _imgoutput;
      system(dispcmd.c_str());

      /* Image file cleanup */
      if (_verbose)
        cout << "Deleting file " << _imgoutput << endl;
      return removefile(_imgoutput);
    }
};

#endif /* lddgraph_HXX */

