#include <gtest/gtest.h>

#include "../src/Database/Database.h"
#include "../src/EnvironmentReader/EnvironmentReader.h"
#include "../src/Database/Auth.h"
#include "../src/Logger/Logger.h"

class UserTest : public ::testing::Test {
protected:
    static void SetUpTestSuite() {
        Logger::create("Logs");
        EnvironmentReader::getEnvReader();
        const std::string connString = EnvironmentReader::getConnString();
        Database::setConnString(connString);
    }
};

TEST_F(UserTest, AccountCreationIncreasesNumberOfAccounts) {
    const auto &database = Database::getDatabaseInstance();
    const int numberOfUsersBefore = database.getNumberOfUsers();
    const Auth auth("AccountCreationIncreasesNumberOfAccounts","test");
    auto user = auth.createAccount();
    const int numberOfUsersAfter = database.getNumberOfUsers();
    ASSERT_EQ(numberOfUsersBefore+1, numberOfUsersAfter);
}

TEST_F(UserTest, NewAccountDetailsTest) {
    const auto &database = Database::getDatabaseInstance();
    std::string username = "NewAccountDetailsTest";
    const Auth auth(username,"test");
    const auto expectedUser = auth.createAccount();
    const auto actualUser = database.getUserByUsername(username);
    ASSERT_EQ(expectedUser, actualUser);
}

TEST_F(UserTest, NoDuplicateUsername) {
    const std::string username = "NoDuplicateUsername";
    const Auth auth(username,"test");
    const auto expectedUser = auth.createAccount();
    const Auth auth1(username,"test2");
    // ReSharper disable once CppNoDiscardExpression
    ASSERT_THROW(auth1.createAccount(),pqxx::unique_violation);
}

TEST_F(UserTest, TestLoginValidCredentialsShouldSucceed) {
    const std::string username = "TestLoginValid";
    const Auth auth(username,"test");
    const auto expectedUser = auth.createAccount();
    const Auth auth1(username,"test");
    const auto actualUser = auth1.login();
    ASSERT_EQ(expectedUser, actualUser);
}

TEST_F(UserTest, TestLoginInvalidCredentialsShouldFail) {
    const std::string username = "LoginTestInvalid";
    const Auth auth(username,"test");
    const auto expectedUser = auth.createAccount();
    const Auth auth1(username,"test1");
    // ReSharper disable once CppNoDiscardExpression
    ASSERT_THROW(auth1.login(), std::exception);
}