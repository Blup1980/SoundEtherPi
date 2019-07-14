cmake_minimum_required (VERSION 2.6)
project (SoundEtherPi)
# The version number.
set (SoundEtherPi_VERSION_MAJOR 1)
set (SoundEtherPi_VERSION_MINOR 0)




# configure a header file to pass some of the CMake settings
# to the source code
configure_file (
  "${PROJECT_SOURCE_DIR}/SoundEtherPiConfig.h.in"
  "${PROJECT_BINARY_DIR}/SoundEtherPiConfig.h"
  )
 
# add the binary tree to the search path for include files
# so that we will find SoundEtherPiConfig.h
include_directories("${PROJECT_BINARY_DIR}")


set(Boost_USE_STATIC_LIBS OFF) 
set(Boost_USE_MULTITHREADED ON)  
set(Boost_USE_STATIC_RUNTIME OFF) 
find_package(Boost 1.65.0 COMPONENTS process) 

if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS}) 
    add_executable(SoundEtherPi SoundEtherpi.cpp EtherBerry.cpp)
    target_link_libraries(SoundEtherPi ${Boost_LIBRARIES})
endif()

