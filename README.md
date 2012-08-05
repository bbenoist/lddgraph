lddgraph
========

lddgraph is a small C++ tool which creates dependencies graphs of dynamically
linked binaries using ldd and Graphviz.

Feel free to use, modify, contribute and redistribute this code.

Usage:  
  lddgraph [options] file

Options:  
  -i <library>  Ignore a specific library.  
  -e <file>     Export image file.  
  -f <format>   Output image format. Use 'dot -T?' for a complete list.  
  -g <file>     Export Graphviz diagram.  
  -t            Use LD_TRACE_LOADED_OBJECTS instead of ldd.  
  -q            Quiet mode.  
  -v            Verbose mode.

*This code is licensed under the terms specified in the LICENSE.BSD file.*

To build this code, you can use the following commands :  
 *mkdir build && cd build*  
 *cmake .. -DCMAKE_BUILD_STYPE:STRING=Release*  
 *make*

Use the make install command if you want to install lddgraph to the
*CMAKE_INSTALL_PREFIX* directory. You can use the
_-DCMAKE_INSTALL_PREFIX:PATH=/your/path_ option to configure cmake with your
preferred one.

