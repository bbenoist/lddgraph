#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#                              lddgraph
# Small C++ tool which creates dependencies graphs of dynamically linked
# binaries using ldd and Graphviz.
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
# This module contains the following functions:
#
# git_version (source_dir version default_version)
#   Extracts the current git version by using git describe. This module needs
#   Git to be installed but doesn't requires it. If Git is not available or if a
#   .git directory/file is not available in the source_dir argument, the version
#   will be the default one given also as argument.
#
#   Arguments:
#     source_dir
#       The directory where the git describe command has to be executed
#     version
#       The version string extracted by this function
#     default_version
#       The default version to use in case of unavailability
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
# This code is licensed under the terms specified in the LICENSE.BSD file
# https://github.com/bbenoist/lddgraph/blob/master/LICENSE.BSD
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
function (git_version _source_dir _version _default_version)
  # If git wasn't previously used, we try to find it
  if (NOT DEFINED GIT_FOUND)
    find_package (Git)
  endif ()
  # If there is no .git directory in the source folder, we set the version to
  # its default text value given as argument
  if (NOT EXISTS "${_source_dir}/.git" OR NOT GIT_FOUND)
    set (${_version} "${_default_version}" PARENT_SCOPE)
  else ()
    # Trying to obtain the current git version and setting _version to its value
    execute_process (
      COMMAND "${GIT_EXECUTABLE}" describe --always --long --dirty=-dirty
      WORKING_DIRECTORY "${_source_dir}"
      RESULT_VARIABLE res
      OUTPUT_VARIABLE out
      ERROR_QUIET
      OUTPUT_STRIP_TRAILING_WHITESPACE)
    if (NOT res EQUAL 0)
      set (out "${out}-${res}-NOTFOUND")
    endif ()
    set (${_version} "${out}" PARENT_SCOPE)
  endif ()
endfunction ()
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
