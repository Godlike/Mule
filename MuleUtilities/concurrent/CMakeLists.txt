# Copyright (C) 2018 by Godlike
# This code is licensed under the MIT license (MIT)
# (http://opensource.org/licenses/MIT)

cmake_minimum_required(VERSION 3.4)
cmake_policy(VERSION 3.4)

find_package(Threads)

if (Threads_FOUND)
    include(MuleInstallInfo)

    install( DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/include/
        DESTINATION ${MULE_INSTALL_INCLUDE_DIR}
        COMPONENT mule_headers
        FILES_MATCHING
            PATTERN "*.hpp"
                PERMISSIONS OWNER_WRITE OWNER_READ GROUP_READ WORLD_READ
            PATTERN "*.imp"
                PERMISSIONS OWNER_WRITE OWNER_READ GROUP_READ WORLD_READ
    )
else()
    message(WARNING "No Threads package was found")
    message(WARNING "Ignoring concurrent part")
endif()
