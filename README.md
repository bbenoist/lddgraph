lddgraph
========

lddgraph is a small C++ tool which creates dependencies graphs of dynamically
linked binaries using ldd and Graphviz.

Feel free to use, modify, contribute and redistribute this code.

Usage:  
  lddgraph [options] file

Options:  
  -i LIBRARY, --ignore=LIBRARY	Ignore a specific library.  
  -I TEXT, --ignore-text=TEXT	Ignore libraries when their path contains the text.  
  -e FILE, --image=FILE		Export image file.  
  -f FORMAT, --image-format=FORMAT  
				Output image format. Use 'dot -T?' for a complete list.  
  -g FILE, --graphviz		Export Graphviz diagram.  
  -t, --trace-loaded-objects	Use LD_TRACE_LOADED_OBJECTS instead of ldd.  
  -q, --quiet			Quiet mode.  
  -V, --verbose			Verbose mode.  
  -h, --help			Print this message and exit.  
  -v, --version			Print the version number of lddgraph and exit.


To build this code, you can use the following commands :  
 *mkdir build && cd build*  
 *cmake .. -DCMAKE_BUILD_STYPE:STRING=Release*  
 *make*

Use the make install command if you want to install lddgraph to the
*CMAKE_INSTALL_PREFIX* directory. You can use the
_-DCMAKE_INSTALL_PREFIX:PATH=/your/path_ option to configure cmake with your
preferred one.

For bug reporting instructions, please see:  
https://github.com/bbenoist/lddgraph/issues

Copyright (C) 2012 Baptist BENOIST  
This code is licensed under the terms specified in the LICENSE.BSD file.
