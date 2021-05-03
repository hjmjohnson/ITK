# Provides itk_clangtidy_setup to assist with maintaining consistent
# c++ best practices across the ITK toolkit
#
# Clang-tidy version 8.0 or greater is required
#
# The ITK C++ best practices guidelines are represented by clang-tidy
# rules defined in ${ITK_SOURCE_DIR}/.clang-tidy
#
option(ITK_USE_CLANGTIDY "Enable the use of clang-tidy enforce coding best practices." ${BUILD_TESTING})
mark_as_advanced(ITK_USE_CLANGTIDY)

if ( ITK_USE_CLANGTIDY AND NOT EXISTS "${CLANGTIDY_EXECUTABLE}" )
  find_program(CLANGTIDY_EXECUTABLE NAMES clang-tidy-13 clang-tidy-12 clang-tidy-11 clang-tidy-10 clang-tidy-9 clang-tidy-9 clang-tidy )
  if(CLANGTIDY_EXECUTABLE AND EXISTS "${CLANGTIDY_EXECUTABLE}")
    mark_as_advanced(CLANGTIDY_EXECUTABLE)
  else()
    unset(CLANGTIDY_EXECUTABLE)
    unset(CMAKE_CXX_CLANG_TIDY)
    message(FATAL_ERROR "Missing suitable clang-tidy executable, set CLANGTIDY_EXECUTABLE variable to desired path")
  endif()

  #-- bugprone-incorrect-roundings.sh*
  #-- google-explicit-constructor.sh*
  #-- google-readability-casting.sh*
  #-- modernize-loop-convert.sh*
  #-- modernize-return-braced-init-list.sh*
  #-- modernize-use-auto.sh*
  #-- modernize-use-bool-literals.sh*
  #-- modernize-use-default-member-init.sh*
  #-- modernize-use-emplace.sh*
  #-- modernize-use-equals-default.sh*
  #-- modernize-use-equals-delete.sh*
  #-- modernize-use-nullptr.sh*
  #-- cppcoreguidelines-init-variables.sh
  #-- misc-unused-parameters.sh
  #-- modernize-pass-by-value.sh
  #-- modernize-raw-string-literal.sh
  #-- modernize-redundant-void-arg.sh
  #-- modernize-use-override.sh
  #-- modernize-use-using.sh
  #-- readability-braces-around-statements.sh
  #-- readability-container-size-empty.sh
  #-- readability-inconsistent-declaration-parameter-name.sh
  #-- readability-isolate-declaration.sh
  #-- readability-make-member-function-const.sh
  #-- readability-misleading-indentation.sh
  #-- readability-non-const-parameter.sh
  #-- readability-redundant-control-flow.sh
  #-- readability-redundant-declaration.sh

  set(CLANG_TIDY_CHECKS "-*,modernize-use-*")
  set(CMAKE_CXX_CLANG_TIDY "${CLANGTIDY_EXECUTABLE};-checks=${CLANG_TIDY_CHECKS};-header-filter='${CMAKE_SOURCE_DIR}/Modules/*/*/include'")

  # Compile commands are required by clang-tidy
  set(CMAKE_EXPORT_COMPILE_COMMANDS ON CACHE BOOL "compile_commands.json file is needed by clang-tidy")

  #--  # Create a preprocessor definition that depends on .clang-tidy content so
  #--  # the compile command will change when .clang-tidy changes.  This ensures
  #--  # that a subsequent build re-runs clang-tidy on all sources even if they
  #--  # do not otherwise need to be recompiled.  Nothing actually uses this
  #--  # definition.  We add it to targets on which we run clang-tidy just to
  #--  # get the build dependency on the .clang-tidy file.
  #--  file(SHA1 ${CMAKE_CURRENT_SOURCE_DIR}/.clang-tidy clang_tidy_sha1)
  #--  set(CLANG_TIDY_DEFINITIONS "CLANG_TIDY_SHA1=${clang_tidy_sha1}")
  #--  unset(clang_tidy_sha1)

  #--  ## configure_file(.clang-tidy .clang-tidy COPYONLY)
endif()
