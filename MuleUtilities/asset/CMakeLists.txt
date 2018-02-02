# Copyright (C) 2018 by Godlike
# This code is licensed under the MIT license (MIT)
# (http://opensource.org/licenses/MIT)

cmake_minimum_required(VERSION 3.4)
cmake_policy(VERSION 3.4)

set(ASSET_HEADERS
    include/mule/asset/Content.hpp
    include/mule/asset/FileReader.hpp
    include/mule/asset/Handler.hpp
    include/mule/asset/SimpleStorage.hpp
)

set(ASSET_SOURCES
    source/Content.cpp
    source/FileReader.cpp
    source/Handler.cpp
    source/SimpleStorage.cpp
)

find_package(Threads)

if (Threads_FOUND)
    set(ASSET_HEADERS
        ${ASSET_HEADERS}
        include/mule/asset/Storage.hpp
    )

    set(ASSET_SOURCES
        ${ASSET_SOURCES}
        source/Storage.cpp
    )
else()
    message(WARNING "No Threads package was found")
    message(WARNING "Ignoring async storage")
endif()

add_library(asset OBJECT
    ${ASSET_HEADERS}
    ${ASSET_SOURCES}
)

include(MuleInstallInfo)

install(
    DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/include/
    DESTINATION ${MULE_INSTALL_INCLUDE_DIR}
    COMPONENT mule_headers
    FILES_MATCHING
        PATTERN "*.hpp"
            PERMISSIONS OWNER_WRITE OWNER_READ GROUP_READ WORLD_READ
        PATTERN "*.imp"
            PERMISSIONS OWNER_WRITE OWNER_READ GROUP_READ WORLD_READ
        PATTERN "utility/asset/FileReader.hpp" EXCLUDE
)

# Needed?
#if (UNIX)
#    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC")
#endif()
