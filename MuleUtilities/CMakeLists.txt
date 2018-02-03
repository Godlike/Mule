# Copyright (C) 2018 by Godlike
# This code is licensed under the MIT license (MIT)
# (http://opensource.org/licenses/MIT)

cmake_minimum_required(VERSION 3.4)
cmake_policy(VERSION 3.4)

project(${MULE_UTILITIES_NAME})

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

if (UNIX)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror -pedantic")
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -s -O3")
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g3 -ggdb3 -O0")
elseif(WIN32)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /MP /W3") # TODO set WX (warning as error)
    add_definitions(-D_CRT_SECURE_NO_WARNINGS)
endif()

## Installation info
include(MuleInstallInfo)

message(STATUS "Version: ${MULE_VERSION}")

include_directories(${MULE_INCLUDE_DIR})

install(
    DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/include/
    DESTINATION ${MULE_INSTALL_INCLUDE_DIR}
    COMPONENT mule_headers
    FILES_MATCHING
        PATTERN "*.hpp"
            PERMISSIONS OWNER_WRITE OWNER_READ GROUP_READ WORLD_READ
        PATTERN "*.imp"
            PERMISSIONS OWNER_WRITE OWNER_READ GROUP_READ WORLD_READ
)

add_subdirectory(asset)
add_subdirectory(concurrent)
add_subdirectory(templates)

set(MULE_UTILITIES_EXTRA)

if (MSVC)
    configure_file(
        ${CMAKE_CURRENT_SOURCE_DIR}/MuleVersionInfo.rc.in
        ${CMAKE_CURRENT_BINARY_DIR}/MuleVersionInfo.rc

        @ONLY
    )

    set(MULE_UTILITIES_EXTRA
        ${MULE_UTILITIES_EXTRA}
        ${CMAKE_CURRENT_BINARY_DIR}/MuleVersionInfo.rc
    )
endif()

add_library(${MULE_UTILITIES_LIB}
    ${MULE_UTILITIES_EXTRA}

    $<TARGET_OBJECTS:asset>
)

set_target_properties(
    ${MULE_UTILITIES_LIB}
    PROPERTIES
        VERSION ${MULE_VERSION}
        SOVERSION ${MULE_SOVERSION}
)

install( TARGETS ${MULE_UTILITIES_LIB}
    COMPONENT mule_libraries
    RUNTIME DESTINATION ${MULE_INSTALL_LIBRARY_DIR}
    LIBRARY DESTINATION ${MULE_INSTALL_LIBRARY_DIR}
    ARCHIVE DESTINATION ${MULE_INSTALL_LIBRARY_DIR}
)

if (MULE_BUILD_DOCUMENTATION)
    find_package(Doxygen)

    if (DOXYGEN_FOUND)
        set(DOXYGEN_INPUT_DIRS
            ${MULE_INCLUDE_DIR}
        )
        set(DOXYGEN_PROJECT_NAME ${PROJECT_NAME})
        string(REPLACE ";" " " DOXYGEN_INPUT "${DOXYGEN_INPUT_DIRS}")

        configure_file(${CMAKE_CURRENT_SOURCE_DIR}/docs/Doxyfile.in ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile)

        file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/docs)
        add_custom_target( docs
            ${DOXYGEN_EXECUTABLE} ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile
            WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/docs
            COMMENT "Generating Mule Utilities API documentation"
        )
    else()
        message(FATAL_ERROR "Doxygen is required to build documentation")
    endif()
endif()


include(CMakePackageConfigHelpers)

write_basic_package_version_file(
    ${CMAKE_CURRENT_BINARY_DIR}/MuleUtilitiesConfigVersion.cmake
    VERSION ${MULE_VERSION}
    COMPATIBILITY SameMajorVersion
)

configure_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/MuleUtilitiesConfig.cmake.in
    ${CMAKE_CURRENT_BINARY_DIR}/MuleUtilitiesConfig.cmake

    @ONLY
)

install(
    FILES
        ${CMAKE_CURRENT_BINARY_DIR}/MuleUtilitiesConfig.cmake
        ${CMAKE_CURRENT_BINARY_DIR}/MuleUtilitiesConfigVersion.cmake
    DESTINATION ${MULE_INSTALL_LIBRARY_DIR}
    COMPONENT mule_headers
)
