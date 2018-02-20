# Copyright (C) 2018 by Godlike
# This code is licensed under the MIT license (MIT)
# (http://opensource.org/licenses/MIT)

set(MULE_UTILITIES_NAME "MuleUtilities" CACHE STRING "Mule project name.")

if(NOT DEFINED MULE_ROOT)
    set(MULE_ROOT "${CMAKE_CURRENT_SOURCE_DIR}" CACHE STRING "Mule root directory.")
endif()

list(APPEND CMAKE_MODULE_PATH "${MULE_ROOT}/MuleUtilities/cmake")

include(SpdlogConfig)

set(MULE_INCLUDE_DIR
    ${MULE_ROOT}/MuleUtilities/include
    ${MULE_ROOT}/MuleUtilities/asset/include
    ${MULE_ROOT}/MuleUtilities/concurrent/include
    ${MULE_ROOT}/MuleUtilities/templates/include
    ${SPDLOG_INCLUDE_DIR}
    CACHE LIST "Mule include directories."
)

if (NOT DEFINED INSTALL_INCLUDE_DIR)
    set(INSTALL_INCLUDE_DIR "include/godlike" CACHE STRING "Path to directory holding headers")
endif()

if (NOT DEFINED INSTALL_LIBRARY_DIR)
    set(INSTALL_LIBRARY_DIR "lib" CACHE STRING "Path to directory holding libraries")
endif()

set(MULE_UTILITIES_LIB ${MULE_UTILITIES_NAME} CACHE STRING "Name of Mule Utilities library")
