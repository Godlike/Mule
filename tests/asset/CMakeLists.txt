# Copyright (C) 2018 by Godlike
# This code is licensed under the MIT license (MIT)
# (http://opensource.org/licenses/MIT)

cmake_minimum_required(VERSION 3.4)
cmake_policy(VERSION 3.4)

project(AssetTest)

set(CMAKE_CXX_STANDARD 14)

find_package(Threads)

set(AdditionalCatchParameters
    WORKING_DIRECTORY "${CMAKE_CURRENT_LIST_DIR}/TestInput"
)

set(TARGET_FOLDER_ROOT "${TARGET_FOLDER_ROOT}/asset")

add_executable(SimpleStorageTest SimpleStorageTest.cpp)
target_link_libraries(SimpleStorageTest ${MULE_UTILITIES_LIB})
ParseAndAddCatchTests(SimpleStorageTest)

add_executable(StorageTest StorageTest.cpp)
target_link_libraries(StorageTest ${MULE_UTILITIES_LIB} ${CMAKE_THREAD_LIBS_INIT})
ParseAndAddCatchTests(StorageTest)

set_target_properties(
    SimpleStorageTest
    StorageTest

    PROPERTIES

    FOLDER "${TARGET_FOLDER_ROOT}"
)
