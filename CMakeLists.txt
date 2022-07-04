cmake_minimum_required(VERSION 3.16)

project(rmcpp VERSION 0.0.1
        LANGUAGES CXX)

file(GLOB_RECURSE sources
        sources/*.cpp)

add_executable(rmcpp-exe ${sources})

add_library(rmcpp ${sources})

target_include_directories(rmcpp PUBLIC
        includes/)

target_include_directories(rmcpp-exe PUBLIC
        includes/)

target_compile_features(rmcpp PUBLIC
        cxx_std_20)

target_compile_features(rmcpp-exe PUBLIC
        cxx_std_20)

set_target_properties(rmcpp PROPERTIES
        LINKER_LANGUAGE CXX)

set_target_properties(rmcpp-exe PROPERTIES
        LINKER_LANGUAGE CXX)