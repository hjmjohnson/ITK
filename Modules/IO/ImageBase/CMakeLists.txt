project(ITKIOImageBase)

# check if the platform has c style IO functions that uses wchar_t * filenames
try_compile(
  ITK_SUPPORTS_WCHAR_T_FILENAME_CSTYLEIO
  ${CMAKE_CURRENT_BINARY_DIR}
  ${CMAKE_CURRENT_SOURCE_DIR}/CMake/itkTestCStyleIOWCharFilename.cxx
  OUTPUT_VARIABLE ITK_SUPPORTS_WCHAR_T_FILENAME_CSTYLEIO_OUTPUT
)

# check if the platform has IO streams constructors that uses wchar_t * filenames
try_compile(
  ITK_SUPPORTS_WCHAR_T_FILENAME_IOSTREAMS_CONSTRUCTORS
  ${CMAKE_CURRENT_BINARY_DIR}
  ${CMAKE_CURRENT_SOURCE_DIR}/CMake/itkTestIOStreamsWCharFilenameConstructors.cxx
  OUTPUT_VARIABLE ITK_SUPPORTS_WCHAR_T_FILENAME_IOSTREAMS_CONSTRUCTORS_OUTPUT
)

# check if the platform can compile fdstream.hxx
if(HAVE_UNISTD_H)
  set(
    ITK_SUPPORTS_FDSTREAM_HPP_COMPILE_DEFINITIONS
    -DITK_HAVE_UNISTD_H=${HAVE_UNISTD_H}
  )
endif()
try_compile(
  ITK_SUPPORTS_FDSTREAM_HPP
  ${CMAKE_CURRENT_BINARY_DIR}
  ${CMAKE_CURRENT_SOURCE_DIR}/CMake/itkTestFDStream.cxx
  CMAKE_FLAGS
    -DINCLUDE_DIRECTORIES:STRING=${ITKIOImageBase_SOURCE_DIR}/include
  COMPILE_DEFINITIONS
    ${ITK_SUPPORTS_FDSTREAM_HPP_COMPILE_DEFINITIONS}
  OUTPUT_VARIABLE ITK_SUPPORTS_FDSTREAM_HPP_OUTPUT
)

configure_file(src/itkIOConfigure.h.in itkIOConfigure.h)

set(ITKIOImageBase_INCLUDE_DIRS ${ITKIOImageBase_BINARY_DIR})
set(ITKIOImageBase_LIBRARIES ITKIOImageBase)
itk_module_impl()

install(
  FILES
    ${ITKIOImageBase_BINARY_DIR}/itkIOConfigure.h
  DESTINATION ${ITKIOImageBase_INSTALL_INCLUDE_DIR}
  COMPONENT Development
)
