# Copyright (C) 2018 by Godlike
# This code is licensed under the MIT license (MIT)
# (http://opensource.org/licenses/MIT)

if (NOT DEFINED SPDLOG_ROOT_DIR)
    set(SPDLOG_ROOT_DIR
        "${MULE_ROOT}/MuleUtilities/third_party/spdlog"
        CACHE STRING "Path to spdlog root directory")
endif()

set(SPDLOG_INCLUDE_DIR
    "${SPDLOG_ROOT_DIR}/include"
    CACHE STRING "Path to spdlog include directory")
