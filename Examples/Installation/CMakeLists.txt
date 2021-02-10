# This is the root ITK CMakeLists file.
cmake_minimum_required(VERSION 3.10.2...3.18)
foreach(p
    ## Only policies introduced after the cmake_minimum_required
    ## version need to explicitly be set to NEW.
    # Policies Introduced by CMake 3.19
       CMP0114  # ExternalProject step targets fully adopt their steps.
       CMP0113  # Makefile generators do not repeat custom commands from target dependencies.
       CMP0112  # Target file component generator expressions do not add target dependencies.
       CMP0111  # An imported target missing its location property fails during generation.
       CMP0110  # add_test() supports arbitrary characters in test names.
       CMP0109  # find_program() requires permission to execute but not to read.
    )
  if(POLICY ${p})
    cmake_policy(SET ${p} NEW)
  endif()
endforeach()

# ==== Define language standard configurations requiring at least c++11 standard
if(CMAKE_CXX_STANDARD EQUAL "98" )
   message(FATAL_ERROR "CMAKE_CXX_STANDARD:STRING=98 is not supported in ITK version 5 and greater.")
endif()

#####
##  Set the default target properties for ITK
if(NOT CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 11) # Supported values are 11, 14, & 17 ( 20 is supported after cmake 3.14).
endif()
if(NOT CMAKE_CXX_STANDARD_REQUIRED)
  set(CMAKE_CXX_STANDARD_REQUIRED ON)
endif()
if(NOT CMAKE_CXX_EXTENSIONS)
  set(CMAKE_CXX_EXTENSIONS OFF)
endif()

# ==== Specify the project build commands
# This project is designed to be built outside the Insight source tree.
project(HelloWorld
        VERSION 0.0.1
        DESCRIPTION "A reference template for making a stand alone application that depends on ITK."
        LANGUAGES CXX
       )

# Find ITK.
find_package(ITK 5.2 REQUIRED)
include(${ITK_USE_FILE})

add_executable(HelloWorld HelloWorld.cxx)
target_link_libraries(HelloWorld ${ITK_LIBRARIES})
