cmake_minimum_required(VERSION 3.26)
project(PasswordKeeper)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_VERBOSE_MAKEFILE ON)

include(cmake/Options.cmake)
include(cmake/CopyHelper.cmake)

include(FetchContent)

set(FETCHCONTENT_QUIET OFF)
set(FETCHCONTENT_UPDATES_DISCONNECTED ON)

FetchContent_Declare(
        pqxx
        GIT_REPOSITORY https://github.com/jtv/libpqxx.git
        GIT_TAG 7.9.2
        CMAKE_ARGS -DSKIP_BUILD_TEST=ON
)
FetchContent_MakeAvailable(pqxx)

find_package(PostgreSQL)

option(RUN_TESTS "Run the test suites" OFF)

add_subdirectory(src)
if(RUN_TESTS)
add_subdirectory(tests)
endif ()