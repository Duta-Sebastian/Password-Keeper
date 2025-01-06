cmake_minimum_required(VERSION 3.26)

project(Password-Keeper-Test-Runner)
set(TEST_PROJECT ${PROJECT_NAME} PARENT_SCOPE)

FetchContent_Declare(
        gtest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG main
)
FetchContent_MakeAvailable(gtest)

add_executable(${PROJECT_NAME}
        main.cpp
        HashingTest.cpp
        UserTest.cpp
        AccountFactoryTest.cpp
        VectorPlusTest.cpp
        AccountTestInsertShowLoggedIn.cpp
        AccountTestNotLoggedIn.cpp
)
include(${CMAKE_HELPER_DIR}/CompilerFlags.cmake)

target_link_libraries(${PROJECT_NAME} PRIVATE ${SRC_PROJECT}_lib gtest gtest_main)

install(TARGETS ${PROJECT_NAME} DESTINATION ${DESTINATION_DIR})

if (EXISTS ${PROJECT_ROOT}/.env)
    copy_files(FILES .env)
endif ()

add_test(NAME ${PROJECT_NAME}_tests COMMAND ${PROJECT_NAME})