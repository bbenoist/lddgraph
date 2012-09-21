#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#                              lddgraph
# Small C++ tool which creates dependencies graphs of dynamically linked
# binaries using ldd and Graphviz.
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
# This code is licensed under the terms specified in the LICENSE.BSD file
# https://github.com/bbenoist/lddgraph/blob/master/LICENSE.BSD
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
cmake_minimum_required (VERSION 2.6)

project (lddgraph CXX)

# CMake custom modules
list (APPEND CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}")

# Defines the LDDGRAPH_VERSION string using Git
include (GitVersion)
git_version ("${PROJECT_SOURCE_DIR}" LDDGRAPH_VERSION "UNVERSIONNED!")
message (STATUS "Current lddgraph version " ${LDDGRAPH_VERSION})

# Defines the copyright
set (LDDGRAPH_COPYRIGHT "Copyright (C) 2012 Baptist BENOIST")

# Configure the necessary files
configure_file (config.in.h config.h)
include_directories (${PROJECT_BINARY_DIR})

add_executable (lddgraph
  contains.hxx
  help.hxx
  lddgraph.hxx
  main.cxx
  system.hxx
  trim.hxx
  version.hxx
  wildcardcompare.hxx
)

# Install
install (TARGETS lddgraph DESTINATION bin)

# Uninstall
configure_file(
  "${PROJECT_SOURCE_DIR}/cmake_uninstall.in.cmake"
  "${PROJECT_BINARY_DIR}/cmake_uninstall.cmake"
    IMMEDIATE @ONLY)
add_custom_target(uninstall
    COMMAND ${CMAKE_COMMAND} -P ${PROJECT_BINARY_DIR}/cmake_uninstall.cmake)

#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
