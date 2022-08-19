#!/bin/bash

# \author Hans J. Johnson
#

COMMIT_INFO="COMP: Script to initiate updating to find_package(Python3)

Now that cmake FindPython3 can be universally
used, prefer to only use that set of variable
names for identifying the python executables.

Intial procesing with manual cleanup by:

ITK/Utilities/Maintenance/FindPython3_ModernizeCMake.sh


NOTE: This script is intended to make it easier
       to identify old find_package(PythonInterp
       uses, but it can not be blindly used.
       each change must be carefully reviewed.
"

# Utility functions
usage() {
cat << EOF
Usage: $0
$COMMIT_INFO
EOF
}

die() {
  echo "$@" 1>&2; exit 1
}

while test $# -gt 0;
do
  opt="$1";
  case "$opt" in
    "-h"|"--help")
      shift;
      help=true
      break;;
    *)
      break;;
  esac
done

if test $help; then
  usage
  exit 1
fi

# Deprecated (since cmake 3.12) variables from the FindPythonInterp
# PYTHONINTERP_FOUND
# PYTHON_EXECUTABLE
# PYTHON_VERSION_STRING
# PYTHON_VERSION_MAJOR
# PYTHON_VERSION_MINOR
# PYTHON_VERSION_PATCH
# Additional deprecated (since cmake 3.12) variables from the FindPythonLibs
# PYTHONLIBS_FOUND
# PYTHON_LIBRARIES
# PYTHON_INCLUDE_PATH
# PYTHON_INCLUDE_DIRS
# PYTHON_DEBUG_LIBRARIES
# PYTHONLIBS_VERSION_STRING
# PYTHON_LIBRARY
# PYTHON_INCLUDE_DIR



cat > /tmp/temp.sed << EOF
s/\bPYTHONINTERP_FOUND\b/Python3_Interpreter_FOUND/g
s/\bPYTHON_EXECUTABLE\b/Python3_EXECUTABLE/g
s/\bPYTHON_VERSION_STRING\b/Python3_VERSION/g
s/\bPYTHON_VERSION_MAJOR\b/Python3_VERSION_MAJOR/g
s/\bPYTHON_VERSION_MINOR\b/Python3_VERSION_MINOR/g
s/\bPYTHON_VERSION_PATCH\b/Python3_VERSION_PATCH/g
s/\bPYTHONLIBS_FOUND\b/Python3_Development_FOUND/g
s/\bPYTHON_LIBRARIES\b/Python3_LIBRARIES/g
s/\bPYTHON_INCLUDE_PATH\b/Python3_XXXXXXX_INCLUDE_PATH_NO_MAPPING_FOR_THIS_PYTHON.h_PATH_FINDER/g
s/\bPYTHON_INCLUDE_DIRS\b/Python3_INCLUDE_DIRS/g
s/\bPYTHON_DEBUG_LIBRARIES\b/Python3_XXXXX_NO_MAPPING_FOR_THIS_DEBUG_LIBRARIES_FLAG/g
s/\bPYTHONLIBS_VERSION_STRING\b/Python3_VERSION/g
s/\bPYTHON_LIBRARY\b/Python3_XXXXXX_LIBARY__NO_MAPPING_FOR_THIS_/g
s/\bPYTHON_INCLUDE_DIR\b/Python3_XXXXXXX_INCLUDE_DIR_NO_MAPPING_FOR_THIS_PYTHON.h_PATH_FINDER/g
s/\bfind_package *( *PythonInterp *REQUIRED *)/find_package(Python3 COMPONENTS Interpreter REQUIRED)/g
s/\bfind_package *( *PythonInterp *)/find_package(Python3 COMPONENTS Interpreter)/g
s/\bfind_package *( *PythonLibs *)/find_package(Python3 COMPONENTS Development)/g
EOF

# Do the replacement
find . -type f -name '*.cmake' -exec gsed -i''  -f /tmp/temp.sed {} \;

cat > /tmp/git_message.txt << EOF
${COMMIT_INFO}
EOF
