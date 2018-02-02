# Copyright (C) 2018 by Godlike
# This code is licensed under the MIT license (MIT)
# (http://opensource.org/licenses/MIT)

set(MULE_UTILITIES_NAME "MuleUtilities" CACHE STRING "Mule project name.")

if(NOT DEFINED MULE_ROOT)
    set(MULE_ROOT "${CMAKE_CURRENT_SOURCE_DIR}" CACHE STRING "Mule root directory.")
endif()

list(APPEND CMAKE_MODULE_PATH "${MULE_ROOT}/Mule/cmake")

#Build flags
if (UNIX)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror -pedantic")
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -s -O3")
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g3 -ggdb3 -O0")
elseif(WIN32)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /MP /W3")
    add_definitions(-D_CRT_SECURE_NO_WARNINGS)
endif()

set(MULE_INCLUDE_DIR
    ${MULE_ROOT}/MuleUtilities/include
    ${MULE_ROOT}/MuleUtilities/asset/include
    ${MULE_ROOT}/MuleUtilities/concurrent/include
    ${MULE_ROOT}/MuleUtilities/templates/include
    CACHE LIST "Mule include directories."
)

if (NOT DEFINED INSTALL_INCLUDE_DIR)
    set(INSTALL_INCLUDE_DIR "include/godlike" CACHE STRING "Path to directory holding headers")
endif()

if (NOT DEFINED INSTALL_LIBRARY_DIR)
    set(INSTALL_LIBRARY_DIR "lib" CACHE STRING "Path to directory holding libraries")
endif()

set(MULE_UTILITIES_LIB ${MULE_UTILITIES_NAME} CACHE STRING "Name of Mule Utilities library")
