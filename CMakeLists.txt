# Copyright (C) 2018 by Godlike
# This code is licensed under the MIT license (MIT)
# (http://opensource.org/licenses/MIT)

cmake_minimum_required(VERSION 3.4)

project(Mule)

option(MULE_BUILD_DOCUMENTATION "Build Mule documentation" OFF)
option(MULE_BUILD_TESTS "Build Mule tests" ON)

message(STATUS "${PROJECT_NAME} configuration:")
message(STATUS "-- MULE_BUILD_DOCUMENTATION: ${MULE_BUILD_DOCUMENTATION}")
message(STATUS "-- MULE_BUILD_TESTS: ${MULE_BUILD_TESTS}")

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

include(MuleUtilitiesConfig)

#Build flags
if (UNIX)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror -pedantic")
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -s -O3")
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g3 -ggdb3 -O0")
elseif(WIN32)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /MP /W3")
    add_definitions(-D_CRT_SECURE_NO_WARNINGS)
endif()

if (NOT CMAKE_ARCHIVE_OUTPUT_DIRECTORY)
    set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/output/lib)
endif()

if (NOT CMAKE_LIBRARY_OUTPUT_DIRECTORY)
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/output/lib)
endif()

if (NOT CMAKE_RUNTIME_OUTPUT_DIRECTORY)
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/output)
endif()

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

add_subdirectory(MuleUtilities)

if (MULE_BUILD_TESTS)
    enable_testing()
    include(CTest)
    set(CATCH_ROOT ${CMAKE_CURRENT_SOURCE_DIR}/third_party/Catch2)
    add_subdirectory(tests)
endif()

get_directory_property(MULE_HAS_PARENT PARENT_DIRECTORY)

if (MULE_HAS_PARENT)
    set(MULE_UTILITIES_LIB ${MULE_UTILITIES_LIB} PARENT_SCOPE)
endif()
