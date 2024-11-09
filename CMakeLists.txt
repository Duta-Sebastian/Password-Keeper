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
        CMAKE_ARGS -DSKIP_BUILD_TEST=on -DINSTALL_TEST=off
)
FetchContent_MakeAvailable(pqxx)
find_package(PostgreSQL)
if (TARGET pqxx)
    # Custom compiler flags
    message("Applying custom compiler flags for pqxx")
    if (MSVC)
        target_compile_options(pqxx PRIVATE /W4 /permissive- /wd4244 /wd4267 /wd4996 /external:anglebrackets /external:W0 /utf-8 /MP)
    else ()
        target_compile_options(pqxx PRIVATE -Wall -Wextra -pedantic)
    endif ()

    # Apply sanitizers
    include(${CMAKE_HELPER_DIR}/CustomStdlibAndSanitizers.cmake)
    set_custom_stdlib_and_sanitizers(pqxx true)
endif ()

option(RUN_TESTS "Run the test suites" OFF)

add_subdirectory(src)
if(RUN_TESTS)
add_subdirectory(tests)
endif ()