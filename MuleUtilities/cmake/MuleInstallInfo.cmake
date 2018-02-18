# Copyright (C) 2018 by Godlike
# This code is licensed under the MIT license (MIT)
# (http://opensource.org/licenses/MIT)

if (NOT DEFINED INSTALL_INCLUDE_DIR)
    set(INSTALL_INCLUDE_DIR "include/godlike" CACHE STRING "Path to directory holding headers")
endif()

if (NOT DEFINED INSTALL_LIBRARY_DIR)
    set(INSTALL_LIBRARY_DIR "lib" CACHE STRING "Path to directory holding libraries")
endif()

if (NOT DEFINED INSTALL_DATA_DIR)
    set(INSTALL_DATA_DIR "share" CACHE STRING "Path to directory holding additional data")
endif()

set(MULE_INSTALL_INCLUDE_DIR ${INSTALL_INCLUDE_DIR})
set(MULE_INSTALL_LIBRARY_DIR ${INSTALL_LIBRARY_DIR}/${MULE_UTILITIES_NAME})
set(MULE_INSTALL_DATA_DIR ${INSTALL_DATA_DIR}/${MULE_UTILITIES_NAME})

set(MULE_VENDOR "Godlike")
set(MULE_DESCRIPTION "Mule Utilities library")
set(MULE_COMMENT "")
set(MULE_COPYRIGHT "Copyright (C) 2018 by Godlike")
set(MULE_LEGAL_TM "Distributed under the MIT license (http://opensource.org/licenses/MIT)")

set(MULE_VERSION_MAJOR 0)
set(MULE_VERSION_MINOR 1)
set(MULE_VERSION_PATCH 0)
set(MULE_VERSION_TWEAK 0)

set(MULE_VERSION "${MULE_VERSION_MAJOR}.${MULE_VERSION_MINOR}.${MULE_VERSION_PATCH}")
set(MULE_SOVERSION "${MULE_VERSION_MAJOR}.${MULE_VERSION_MINOR}")

if (NOT DEFINED SLEIPNIR_VERSION_MAJOR)
    set(SLEIPNIR_VERSION_MAJOR 0)
endif()

if (NOT DEFINED SLEIPNIR_VERSION_MINOR)
    set(SLEIPNIR_VERSION_MINOR 0)
endif()

if (NOT DEFINED SLEIPNIR_VERSION_PATCH)
    set(SLEIPNIR_VERSION_PATCH 0)
endif()

if (NOT DEFINED SLEIPNIR_VERSION_TWEAK)
    set(SLEIPNIR_VERSION_TWEAK 0)
endif()
