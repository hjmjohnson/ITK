###############################################################################
# the macros in charge of dispatching to the language specific macros

macro(itk_wrap_module_all_generators library_name)
  if(ITK_WRAPPING)
    itk_wrap_module_castxml("${library_name}")
    itk_wrap_module_swig_interface("${library_name}")
  endif()
  if(${module_prefix}_WRAP_DOC)
    itk_wrap_module_DOC("${library_name}")
  endif()
  if(${module_prefix}_WRAP_PYTHON AND WRAPPER_LIBRARY_PYTHON)
    itk_wrap_module_python("${library_name}")
  endif()
endmacro()


macro(itk_wrap_submodule_all_generators module)
  if(ITK_WRAPPING)
    itk_wrap_submodule_castxml("${module}")
    itk_wrap_submodule_swig_interface("${module}")
  endif()
  if(${module_prefix}_WRAP_DOC)
    itk_wrap_submodule_DOC("${module}")
  endif()
  if(${module_prefix}_WRAP_PYTHON AND WRAPPER_LIBRARY_PYTHON)
    itk_wrap_submodule_python("${module}" "${WRAPPER_LIBRARY_NAME}")
  endif()
endmacro()


macro(itk_wrap_named_class_all_generators class swig_name)
  if(${module_prefix}_WRAP_PYTHON AND WRAPPER_LIBRARY_PYTHON)
    itk_wrap_named_class_python("${class}" "${swig_name}")
  endif()
  if(${module_prefix}_WRAP_DOC)
    itk_wrap_named_class_DOC("${class}" "${swig_name}")
  endif()
endmacro()

macro(itk_end_wrap_class_all_generators)
endmacro()


macro(itk_wrap_simple_class_all_generators class)
endmacro()


macro(itk_wrap_named_simple_class_all_generators class)
endmacro()


macro(itk_wrap_include_all_generators inc)
  if(ITK_WRAPPING)
    itk_wrap_include_castxml("${inc}")
    itk_wrap_include_swig_interface("${inc}")
  endif()
endmacro()

macro(itk_wrap_template_all_generators name types)
  if(${module_prefix}_WRAP_PYTHON AND WRAPPER_LIBRARY_PYTHON)
    itk_wrap_template_python("${name}" "${types}")
  endif()
endmacro()


macro(itk_wrap_one_type_all_generators wrap_method wrap_class swig_name template_params)
  if(ITK_WRAPPING)
    itk_wrap_one_type_castxml("${wrap_method}" "${wrap_class}" "${swig_name}" "${template_params}")
    itk_wrap_one_type_swig_interface("${wrap_method}" "${wrap_class}" "${swig_name}" "${template_params}")
  endif()
  if(${module_prefix}_WRAP_DOC)
    itk_wrap_one_type_DOC("${wrap_method}" "${wrap_class}" "${swig_name}" "${template_params}")
  endif()
  if(${module_prefix}_WRAP_PYTHON AND WRAPPER_LIBRARY_PYTHON)
    itk_wrap_one_type_python("${wrap_method}" "${wrap_class}" "${swig_name}" "${template_params}")
  endif()
endmacro()


macro(itk_wrap_simple_type_all_generators wrap_class swig_name)
  if(ITK_WRAPPING)
    itk_wrap_simple_type_castxml("${wrap_class}" "${swig_name}")
  endif()
  if(${module_prefix}_WRAP_PYTHON AND WRAPPER_LIBRARY_PYTHON)
    itk_wrap_simple_type_python("${wrap_class}" "${swig_name}")
  endif()
endmacro()



###############################################################################
# ccache management. This option is shared by most of generators, so put it here.
option(ITK_USE_CCACHE "Use ccache to cache swig/castxml/... output and speedup the rebuild." OFF)
mark_as_advanced(ITK_USE_CCACHE)
if(ITK_USE_CCACHE)
  find_program(CCACHE_EXECUTABLE NAMES ccache-swig ccache DOC "ccache executable.")
endif()



###############################################################################
# build the generators list

set(WRAP_ITK_GENERATORS CACHE INTERNAL "Internal generators list.")
set(WRAP_ITK_UNUSED_GENERATORS CACHE INTERNAL "Internal unused generators list.")

# The following list of directories int the "ITK/Wrapping/Generators
# SwigInterface, CastXML, and Python are unconditional, if ITK_WRAPPING is ON, then these must also be ON
list(APPEND WRAP_ITK_GENERATORS "SwigInterface")
add_subdirectory("SwigInterface")
list(APPEND WRAP_ITK_GENERATORS "CastXML")
add_subdirectory("CastXML")
list(APPEND WRAP_ITK_GENERATORS "Python")
add_subdirectory("Python")

if(${module_prefix}_WRAP_DOC)
  list(APPEND WRAP_ITK_GENERATORS "Doc")
  add_subdirectory("Doc")
else()
  list(APPEND WRAP_ITK_UNUSED_GENERATORS "Doc")
endif()

set(WRAP_ITK_GENERATORS ${WRAP_ITK_GENERATORS} CACHE INTERNAL "Internal generators list.")
set(WRAP_ITK_UNUSED_GENERATORS ${WRAP_ITK_UNUSED_GENERATORS} CACHE INTERNAL "Internal unused generators list.")

# The include_directories are added here to be used by Wrapping/ConfigureWrapping.cmake
foreach(lang ${WRAP_ITK_GENERATORS})
  get_directory_property(inc DIRECTORY "${lang}" INCLUDE_DIRECTORIES)
  include_directories(${inc})
endforeach()
