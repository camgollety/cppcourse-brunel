cmake_minimum_required (VERSION 2.6) 
project (Neuron)

set(CMAKE_CXX_FLAGS "-O3 -W -Wall -pedantic -std=c++11")

enable_testing()
add_subdirectory(googletest)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

add_executable (neuron main1.cpp neuron.cc network.cc) 
add_executable (neuron_unittest neuron.cc neuron_unittest.cpp constants.hpp)

target_link_libraries(neuron_unittest gtest_main)
add_test(neuron_unittest neuron_unittest)
