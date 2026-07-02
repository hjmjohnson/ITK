project(ITKDCMTK)

set(ITKDCMTK_THIRD_PARTY 1)

# DCMTK is built in-scope via FetchContent; this module dir has no sources.
set(ITKDCMTK_NO_SRC 1)

include(CMakeParseArguments)

if(DCMTK_USE_ICU)
  option(ITK_USE_SYSTEM_ICU "Use an installed version of ICU" OFF)
  if(NOT ITK_USE_SYSTEM_ICU)
    message(
      FATAL_ERROR
      "DCMTK_USE_ICU requires ITK_USE_SYSTEM_ICU=ON: building ICU from source is incompatible with DCMTK's in-scope FetchContent configuration, which runs DCMTK's find_package(ICU) at configure time. Provide a system ICU or disable DCMTK_USE_ICU."
    )
  endif()
endif()

set(
  _ITKDCMTK_LIB_NAMES
  dcmdata
  dcmpstat
  dcmsr
  dcmqrdb
  dcmimgle
  dcmimage
  dcmjpeg
  dcmjpls
  dcmnet
  dcmiod
  dcmfg
  dcmseg
  dcmpmap
  ijg12
  ijg16
  ijg8
  oflog
  ofstd
  oficonv
)
if(WIN32)
  set(
    ITKDCMTK_LIBDEP_WIN
    iphlpapi
    ws2_32
    netapi32
    wsock32
  )
endif()

#
# if DCMTK is built elsewhere
if(ITK_USE_SYSTEM_DCMTK)
  # assign includes to std module var
  set(ITKDCMTK_SYSTEM_INCLUDE_DIRS ${DCMTK_INCLUDE_DIRS})

  # Module standard library var
  set(ITKDCMTK_LIBRARIES)
  foreach(lib IN LISTS DCMTK_LIBRARIES)
    if(TARGET DCMTK::${lib})
      list(APPEND ITKDCMTK_LIBRARIES DCMTK::${lib})
    else()
      list(APPEND ITKDCMTK_LIBRARIES ${lib})
    endif()
  endforeach()

  # When this module is loaded by an app, load DCMTK too.
  set(
    ITKDCMTK_EXPORT_CODE_INSTALL
    "
set(DCMTK_DIR \"${DCMTK_DIR}\")
find_package(DCMTK REQUIRED NO_MODULE)
"
  )
  set(
    ITKDCMTK_EXPORT_CODE_BUILD
    "
if(NOT ITK_BINARY_DIR)
  set(CMAKE_MODULE_PATH
    \"${CMAKE_CURRENT_SOURCE_DIR}/CMake\" \${CMAKE_MODULE_PATH})
  set(DCMTK_DIR \"${DCMTK_DIR}\")
  find_package(DCMTK REQUIRED NO_MODULE)
endif()
"
  )

  itk_module_impl()
else(ITK_USE_SYSTEM_DCMTK)
  # FetchContent + add_subdirectory builds DCMTK in ITK's scope so it consumes
  # ITK's codec targets directly.
  include(FetchContent)
  include(${CMAKE_CURRENT_LIST_DIR}/DCMTKGitTag.cmake)

  # Pass ITK's codec libraries as the standard find_package variables; in-scope
  # they resolve to ITK's imported targets with their transitive usage requirements.
  set(DCMTK_USE_FIND_PACKAGE ON)
  set(DCMTK_WITH_TIFF ON)
  set(DCMTK_WITH_PNG ON)
  set(DCMTK_WITH_ZLIB ON)
  set(DCMTK_WITH_OPENSSL OFF)
  set(DCMTK_WITH_XML OFF)
  set(TIFF_LIBRARIES ITK::ITKTIFFModule)
  set(JPEG_LIBRARIES ITK::ITKJPEGModule)
  set(PNG_LIBRARIES ITK::ITKPNGModule)
  set(ZLIB_LIBRARIES ITK::ITKZLIBModule)

  # DCMTK build options; compiler and language-standard settings inherit from ITK's scope.
  set(BUILD_APPS OFF)
  set(DCMTK_ENABLE_CXX11 ON)
  set(DCMTK_FORCE_FPIC_ON_UNIX ON)
  set(DCMTK_DEFAULT_DICT builtin)
  set(DCMTK_WITH_DOXYGEN OFF)
  set(DCMTK_WITH_SNDFILE OFF)
  set(DCMTK_WITH_WRAP OFF)
  set(DCMTK_ENABLE_PRIVATE_TAGS ON)

  # Charset conversion: system ICU when DCMTK_USE_ICU is set, otherwise
  # DCMTK's built-in oficonv data.
  if(DCMTK_USE_ICU)
    set(DCMTK_WITH_ICU ON)
    set(DCMTK_WITH_STDLIBC_ICONV OFF)
    set(DCMTK_ENABLE_CHARSET_CONVERSION "ICU" CACHE INTERNAL "") # NOTE: DCMTK requires a cache entry
  else()
    set(DCMTK_WITH_ICU OFF)
    set(DCMTK_ENABLE_BUILTIN_OFICONV_DATA ON)
    set(DCMTK_ENABLE_CHARSET_CONVERSION "oficonv" CACHE INTERNAL "")
  endif()

  set(DCMTK_OVERWRITE_WIN32_COMPILER_FLAGS OFF)

  # Silence DCMTK third-party warnings here because add_subdirectory() runs
  # before itk_module_impl() would disable them.
  itk_module_warnings_disable(C CXX)

  # No EXCLUDE_FROM_ALL: it leaks onto ITK's own test targets and drops them
  # from ALL. DCMTK's libraries are needed by ITKIODCMTK and it builds no apps
  # (BUILD_APPS OFF) or tests.
  FetchContent_Declare(
    dcmtk
    GIT_REPOSITORY ${DCMTK_GIT_REPOSITORY}
    GIT_TAG ${DCMTK_GIT_TAG}
  )

  FetchContent_MakeAvailable(dcmtk)

  # DCMTK:: IMPORTED INTERFACE wrappers (not ALIAS): IMPORTED preserves the
  # namespaced name in ITKTargets.cmake, matching what find_package(DCMTK)
  # yields for downstream consumers.
  foreach(_dcmtk_lib IN LISTS _ITKDCMTK_LIB_NAMES)
    set(_dcmtk_target "${_dcmtk_lib}${DCMTK_LIBRARY_SUFFIX}")
    if(TARGET "${_dcmtk_target}")
      if(NOT TARGET "DCMTK::${_dcmtk_target}")
        add_library("DCMTK::${_dcmtk_target}" INTERFACE IMPORTED GLOBAL)
        target_link_libraries(
          "DCMTK::${_dcmtk_target}"
          INTERFACE
            "${_dcmtk_target}"
        )
      endif()
      list(APPEND ITKDCMTK_LIBRARIES "DCMTK::${_dcmtk_target}")
    endif()
  endforeach()
  unset(_dcmtk_lib)
  unset(_dcmtk_target)

  # Build-tree consumers: locate DCMTKConfig.cmake in ITK's build root. The
  # build-tree export was written by export(TARGETS NAMESPACE), which
  # mis-prefixes superproject targets (e.g. DCMTK::ITK::*Module); strip the
  # prefix from any reference that is not an existing target after import.
  # Matches the fix proposed upstream in DCMTK/dcmtk#150.
  list(JOIN _ITKDCMTK_LIB_NAMES " " _itkdcmtk_lib_names_spaced)
  set(
    ITKDCMTK_EXPORT_CODE_BUILD
    "
if(NOT ITK_BINARY_DIR)
  set(DCMTK_DIR \"${CMAKE_BINARY_DIR}\")
  find_package(DCMTK REQUIRED NO_MODULE)
  foreach(_itkdcmtk_lib ${_itkdcmtk_lib_names_spaced})
    if(TARGET DCMTK::\${_itkdcmtk_lib})
      get_target_property(_itkdcmtk_ll DCMTK::\${_itkdcmtk_lib} INTERFACE_LINK_LIBRARIES)
      if(_itkdcmtk_ll)
        set(_itkdcmtk_ll_new \"\")
        foreach(_itkdcmtk_entry IN LISTS _itkdcmtk_ll)
          set(_itkdcmtk_name \"\${_itkdcmtk_entry}\")
          set(_itkdcmtk_link_only 0)
          if(_itkdcmtk_entry MATCHES \"^\\\\\$<LINK_ONLY:(.+)>\$\")
            set(_itkdcmtk_name \"\${CMAKE_MATCH_1}\")
            set(_itkdcmtk_link_only 1)
          endif()
          if(_itkdcmtk_name MATCHES \"^DCMTK::(.+)\$\" AND NOT TARGET \"\${_itkdcmtk_name}\")
            set(_itkdcmtk_name \"\${CMAKE_MATCH_1}\")
          endif()
          if(_itkdcmtk_link_only)
            list(APPEND _itkdcmtk_ll_new \"\$<LINK_ONLY:\${_itkdcmtk_name}>\")
          else()
            list(APPEND _itkdcmtk_ll_new \"\${_itkdcmtk_name}\")
          endif()
        endforeach()
        if(NOT \"\${_itkdcmtk_ll_new}\" STREQUAL \"\${_itkdcmtk_ll}\")
          set_target_properties(DCMTK::\${_itkdcmtk_lib} PROPERTIES
            INTERFACE_LINK_LIBRARIES \"\${_itkdcmtk_ll_new}\")
        endif()
        unset(_itkdcmtk_ll_new)
        unset(_itkdcmtk_entry)
        unset(_itkdcmtk_name)
        unset(_itkdcmtk_link_only)
      endif()
      unset(_itkdcmtk_ll)
    endif()
  endforeach()
  unset(_itkdcmtk_lib)
endif()
"
  )
  unset(_itkdcmtk_lib_names_spaced)
  # Install-tree consumers: locate DCMTKConfig.cmake under ITK_INSTALL_PREFIX.
  set(
    ITKDCMTK_EXPORT_CODE_INSTALL
    "
set(DCMTK_DIR \"\${ITK_INSTALL_PREFIX}/${CMAKE_INSTALL_LIBDIR}/cmake/dcmtk\")
find_package(DCMTK REQUIRED NO_MODULE)
"
  )

  itk_module_impl()
endif(ITK_USE_SYSTEM_DCMTK)

if(MSVC)
  # DCMTK's osconfig.h guards C++11/14/17 on __cplusplus, which MSVC underreports without this.
  target_compile_options(ITKDCMTKModule INTERFACE /Zc:__cplusplus)
endif()
