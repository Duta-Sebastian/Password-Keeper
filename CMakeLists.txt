cmake_minimum_required(VERSION 3.26)

# NOTE: update executable name in .github/workflows/cmake.yml:25 when changing executable name in this file
# for now, the project name is used as the executable name
project(Password-Keeper)
# set(CMAKE_PROJECT_VERSION_MAJOR 0)
# set(CMAKE_PROJECT_VERSION_MINOR 0)
# set(CMAKE_PROJECT_VERSION_PATCH 1)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_VERBOSE_MAKEFILE ON)

include(cmake/Options.cmake)

###############################################################################

# external dependencies with FetchContent
# include(FetchContent)
#
# set(FETCHCONTENT_QUIET OFF)
# set(FETCHCONTENT_UPDATES_DISCONNECTED ON)
#
# NOTE: Also update env vars used for caching in
#         - .github/actions/configure-cmake/action.yml
#         - .github/workflows/cmake.yml
# FetchContent_Declare(
#         SomeLib
#         GIT_REPOSITORY https://github.com/<SomeUser>/<SomeLib>.git
#         GIT_TAG        <some_git_hash> # <which tag/branch @ <some_date>>
#         GIT_SHALLOW    1  # works only with branches or tags, not with arbitrary commit hashes
# )
#
# FetchContent_MakeAvailable(SomeLib)

include(FetchContent)

set(FETCHCONTENT_QUIET OFF)
set(FETCHCONTENT_UPDATES_DISCONNECTED ON)
FetchContent_Declare(
        pq
        GIT_REPOSITORY https://git.postgresql.org/git/postgresql.git
        GIT_TAG master
)

FetchContent_MakeAvailable(pq)

FetchContent_Declare(
     pqxx
     GIT_REPOSITORY https://github.com/jtv/libpqxx.git
     GIT_TAG 7.9.2
)

FetchContent_MakeAvailable(pqxx)


###############################################################################
###############################################################################
# NOTE: update executable name in .github/workflows/cmake.yml:25 when changing name here
add_executable(${PROJECT_NAME}
        main.cpp
        Database/Database.cpp
        EnvironmentReader/EnvironmentReader.cpp
        EnvironmentReader/EnvironmentReader.h
        User/User.cpp
        User/User.h
        Utils/PasswordHash.cpp
        Utils/PasswordHash.h
        Database/Auth.cpp
        Database/Auth.h
        Database/Auth.cpp
        Utils/EnvVarManager.cpp
        Utils/EnvVarManager.h
)

include(cmake/CompilerFlags.cmake)

###############################################################################
target_include_directories(${PROJECT_NAME} SYSTEM PRIVATE infrastructure)
target_include_directories(${PROJECT_NAME} SYSTEM PRIVATE ext/include/digestpp)

target_include_directories(${PROJECT_NAME} PRIVATE ${PQ_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} PRIVATE ${PQ_LIBRARIES})

target_include_directories(${PROJECT_NAME} PRIVATE ${pqxx_SOURCE_DIR}/include)
target_link_directories(${PROJECT_NAME} PRIVATE ${pqxx_SOURCE_DIR}/lib)
target_link_libraries(${PROJECT_NAME} PRIVATE pqxx)


# use SYSTEM so cppcheck and clang-tidy do not report warnings from these directories
# target_include_directories(${PROJECT_NAME} SYSTEM PRIVATE ext/<SomeHppLib>/include)
# target_include_directories(${PROJECT_NAME} SYSTEM PRIVATE ${<SomeLib>_SOURCE_DIR}/include)
# target_link_directories(${PROJECT_NAME} PRIVATE ${<SomeLib>_BINARY_DIR}/lib)
# target_link_libraries(${PROJECT_NAME} <SomeLib>)

###############################################################################
# copy binaries to "bin" folder; these are uploaded as artifacts on each release
# DESTINATION_DIR is set as "bin" in cmake/Options.cmake:6
install(TARGETS ${PROJECT_NAME} DESTINATION ${DESTINATION_DIR})
if (APPLE)
    install(FILES launcher.command DESTINATION ${DESTINATION_DIR})
endif ()

include(cmake/CopyHelper.cmake)
copy_files(FILES tastatura.txt)