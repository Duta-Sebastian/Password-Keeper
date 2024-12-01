cmake_minimum_required(VERSION 3.26)

project(Password-Keeper-src)
set(SRC_PROJECT ${PROJECT_NAME} PARENT_SCOPE)

add_library(${PROJECT_NAME}_lib
        Database/Database.cpp
        EnvironmentReader/EnvironmentReader.cpp
        User/User.cpp
        Utils/PasswordHash.cpp
        Database/Auth.cpp
        Utils/EnvVarManager.cpp
        Logger/Logger.cpp
        Exceptions/DatabaseExceptions/DatabaseExceptions.cpp
        Accounts/Account.cpp
        Accounts/BankAccount.cpp
        Accounts/EmailAccount.cpp
        Accounts/SocialMediaAccount.cpp
        Accounts/AccountFactory.cpp
        Accounts/AccountFactory.h
        Utils/VectorPlusTemplate.cpp
        Utils/AccountType.cpp
        Utils/AddAccountCommandTemplate.cpp
        Utils/ShowAccountsCommand.cpp
)

target_include_directories(${PROJECT_NAME}_lib SYSTEM PRIVATE
        ${pqxx_SOURCE_DIR}/include
)

target_include_directories(${PROJECT_NAME}_lib SYSTEM PUBLIC
        ../ext/include/digestpp
)

target_include_directories(${PROJECT_NAME}_lib PUBLIC
        Database
        EnvironmentReader
        User
        Utils
        Logger
        Exceptions
        Exceptions/DatabaseExceptions
        Accounts
)

target_link_directories(${PROJECT_NAME}_lib PUBLIC ${pqxx_SOURCE_DIR}/lib)
target_link_libraries(${PROJECT_NAME}_lib PUBLIC pqxx)

add_executable(${PROJECT_NAME}
        main.cpp
        Exceptions/DatabaseExceptions/AccountExceptions.cpp
        Exceptions/DatabaseExceptions/AccountExceptions.h
)
target_link_libraries(${PROJECT_NAME} PRIVATE ${PROJECT_NAME}_lib)

include(${CMAKE_HELPER_DIR}/CompilerFlags.cmake)

install(TARGETS ${PROJECT_NAME} DESTINATION ${DESTINATION_DIR})
if (APPLE)
    install(FILES ${PROJECT_ROOT}/launcher.command DESTINATION ${DESTINATION_DIR})
endif ()

copy_files(FILES tastatura.txt)
if (EXISTS ${PROJECT_ROOT}/.env)
    copy_files(FILES .env)
endif ()
