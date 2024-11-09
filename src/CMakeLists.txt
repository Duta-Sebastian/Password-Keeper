cmake_minimum_required(VERSION 3.26)

# NOTE: update executable name in .github/workflows/cmake.yml:25 when changing executable name in this file
# for now, the project name is used as the executable name
project(Password-Keeper-src)
set(SRC_PROJECT ${PROJECT_NAME} PARENT_SCOPE)
# set(CMAKE_PROJECT_VERSION_MAJOR 0)
# set(CMAKE_PROJECT_VERSION_MINOR 0)
# set(CMAKE_PROJECT_VERSION_PATCH 1)

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
        Logger/Logger.cpp
        Logger/Logger.h
)
include(${CMAKE_HELPER_DIR}/CompilerFlags.cmake)
###############################################################################
target_include_directories(${PROJECT_NAME} SYSTEM PRIVATE ../infrastructure)
target_include_directories(${PROJECT_NAME} SYSTEM PRIVATE ../ext/include/digestpp)

target_include_directories(${PROJECT_NAME} SYSTEM PRIVATE ${pqxx_SOURCE_DIR}/include)
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
    install(FILES ${PROJECT_ROOT}/launcher.command DESTINATION ${DESTINATION_DIR})
endif ()

copy_files(FILES tastatura.txt)
if (EXISTS ${PROJECT_ROOT}/.env)
    copy_files(FILES .env)
endif ()
