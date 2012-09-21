//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//                             lddgraph
// Small C++ tool which creates dependencies graphs of dynamically linked
// binaries using ldd and Graphviz.
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// This code is licensed under the terms specified in the LICENSE.BSD file
// https://github.com/bbenoist/lddgraph/blob/master/LICENSE.BSD
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#include <string.h>
#include <getopt.h>
#include <unistd.h>
#include <iostream>
#include "progname.h"
#include "lddgraph.hxx"
#include "help.hxx"
#include "version.hxx"
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
using namespace std;
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

static const struct option longopts[] =
{
  { "ignore", required_argument, NULL, 'i' },
  { "ignore-text", required_argument, NULL, 'I' },
  { "image", required_argument, NULL, 'e' },
  { "image-format", required_argument, NULL, 'f' },
  { "graphviz", required_argument, NULL, 'g' },
  { "ld-trace-loaded-objects", no_argument, NULL, 't' },
  { "quiet", no_argument, NULL, 'q' },
  { "verbose", no_argument, NULL, 'V' },
  { "help", no_argument, NULL, 'h' },
  { "version", no_argument, NULL, 'v' },
  { "binary", required_argument, NULL, 'b' },
  { NULL, 0, NULL, 0 }
};
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

// Entry point for lddgraph
int main(int argc, char* argv[])
{
  program_name = argv[0];

  /* Prints output when no arguments where specified */
  if (argc < 2)
  {
    printhelp();
    exit(EXIT_SUCCESS);
  }

  lddgraph lddg;

  int optc;
  while ((optc = getopt_long (argc, argv, "b:vhi:I:e:f:g:tqV", longopts, NULL)) != -1)
  {
    switch (optc)
    {
      case 'v':
      {
        printversion();
        exit(EXIT_SUCCESS);
      } break;
      case 'h':
      {
        printhelp();
        exit(EXIT_SUCCESS);
      } break;
      case 'i':
      {
        vector<string> ignorelist = lddg.getignorelist();
        string val = optarg;
        ignorelist.push_back(trim(val));
        lddg.setignorelist(ignorelist);
      } break;
      case 'I':
      {
        vector<string> ignorepatterns = lddg.getignorepatterns();
        string val = optarg;
        ignorepatterns.push_back(trim(val));
        lddg.setignorepatterns(ignorepatterns);
      } break;
      case 'e':
      {
        lddg.setimgmode(true);
        lddg.setimgoutput(optarg);
      } break;
      case 'f':
      {
        lddg.setimgformat(optarg);
      } break;
      case 'g':
      {
        lddg.setgvmode(true);
        lddg.setgvoutput(optarg);
      } break;
      case 't':
      {
        lddg.setuseldd(false);
      } break;
      case 'q':
      {
        lddg.setquiet(true);
      } break;
      case 'V':
      {
        lddg.setverbose(true);
      } break;
      default:
      {
        abort();
      } break;
    }
  }

  lddg.setinput(argv[argc - 1]);

  // Start the lddgraph processing
  if (lddg.run())
    exit(EXIT_SUCCESS);
  else
    exit(EXIT_FAILURE);
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
