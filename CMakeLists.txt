cmake_minimum_required(VERSION 3.1)

# Fail immediately if not using an out-of-source build
if(CMAKE_CURRENT_SOURCE_DIR STREQUAL CMAKE_CURRENT_BINARY_DIR)
  message(FATAL_ERROR
    "In-source builds are not supported.  Please create a build directory "
    "separate from the source directory")
endif()

project(ZFP)

add_subdirectory(src)

option(BUILD_ZFORP "Build Fortran library" ON)
if(BUILD_ZFORP)
  add_subdirectory(fortran)
endif()

include(CTest)
if(BUILD_TESTING)
  enable_testing()
  add_subdirectory(tests)
endif()

#------------------------------------------------------------------------------#
# Build type: one of None, Debug, Release, RelWithDebInfo, MinSizeRel
#------------------------------------------------------------------------------#
if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
  set_property(CACHE CMAKE_BUILD_TYPE PROPERTY VALUE Release)
endif()
