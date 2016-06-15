cmake_minimum_required(VERSION 2.8.4)
project(cpp_sandbox)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -march=native")
set(CMAKE_CXX_FLAGS_RELWITHDEBINFO)
add_definitions(-D_ELPP_STACKTRACE_ON_CRASH=1)
add_definitions(-D_ELPP_PERFORMANCE_MICROSECONDS=1)
add_definitions(-DDEBUG=1)

###############################
# set output path
###############################
set(LIBRARY_OUTPUT_PATH "${PROJECT_BINARY_DIR}/lib" CACHE PATH "Output directory for library" )
set(EXECUTABLE_OUTPUT_PATH "${PROJECT_BINARY_DIR}/bin" CACHE PATH "Output directory for executables" )


######################
# boost
######################
if(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
  set(Boost_INCLUDE_DIR "/usr/local/boost/include")
  set(Boost_LIBRARY_DIR "/usr/local/boost/lib")
endif()

FIND_PACKAGE(Boost COMPONENTS filesystem thread program_options system date_time chrono log iostreams serialization regex REQUIRED)
if (Boost_FOUND)
  message(STATUS "Found 'boost library'")
  include_directories(${Boost_INCLUDE_DIR})
  message(STATUS "  boost lib dir:${Boost_LIBRARY_DIRS}")
  message(STATUS "  boost include dir:${Boost_INCLUDE_DIR}")
  message(STATUS "LINK DIR:")

  foreach(var ${Boost_LIBRARIES})
    message(STATUS "  ${var}")
  endforeach(var)
else()
  message(FATAL_ERROR "Couldn't find Boost library.")
endif()

##########################
# opencv
##########################
find_package(OpenCV REQUIRED)
if(OpenCV_FOUND)
  message(STATUS "opencv lib dir:${OpenCV_LIBRARY_DIRS}")
  message(STATUS "opencv include dir:${OpenCV_INCLUDE_DIRS}")
  message(STATUS "opencv config path:${OpenCV_CONFIG_PATH}")
else()
  message(FATAL_ERROR "Couldn't find OpenCV")
endif()

ADD_SUBDIRECTORY("exe")

execute_process(
	COMMAND git log -n 1 --oneline --no-decorate
	OUTPUT_VARIABLE GIT_LOG
)
string(STRIP ${GIT_LOG} GIT_LOG)

message(STATUS "cmake_binary_dir:${CMAKE_BINARY_DIR}")

configure_file ( "version.hpp.in" "version.hpp" )
