cmake_minimum_required(VERSION 3.26)
project(PasswordKeeper)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_VERBOSE_MAKEFILE ON)

set(PROJECT_ROOT "${CMAKE_CURRENT_LIST_DIR}")
set(CMAKE_HELPER_DIR "${PROJECT_ROOT}/cmake")
include(${CMAKE_HELPER_DIR}/Options.cmake)
include(${CMAKE_HELPER_DIR}/CopyHelper.cmake)

include(FetchContent)

set(FETCHCONTENT_QUIET OFF)
set(FETCHCONTENT_UPDATES_DISCONNECTED ON)

FetchContent_Declare(
        pqxx
        GIT_REPOSITORY https://github.com/jtv/libpqxx.git
        GIT_TAG 7.9.2
)
FetchContent_MakeAvailable(pqxx)

find_package(PostgreSQL)

add_subdirectory(src)
if (RUN_TESTS)
    include(CTest)
    enable_testing()
    add_subdirectory(tests)
endif ()