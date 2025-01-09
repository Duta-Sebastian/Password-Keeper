#include <gtest/gtest.h>

#include <AccountFactory.h>
#include <Auth.h>
#include <Database.h>
#include <EnvironmentReader.h>
#include <Logger.h>

class AccountTestInsertShowLoggedIn : public ::testing::Test {
protected:
    static void SetUpTestSuite() {
        EnvironmentReader::getEnvReader();
        const std::string connString = EnvironmentReader::getConnString();
        Database::setConnString(connString);
        const auto auth = Auth("test","test");
        const auto currentUser = auth.createAccount();
    }
};

TEST_F(AccountTestInsertShowLoggedIn, bankAccountInsert) {
    const auto bankAccountFactory =
    AccountFactory::accountFactory(AccountType::BankAccountType,
                               {
                                   {"username", "sebi11"}, {"password", "1234"},
                                   {"IBAN", "123412412"}, {"bank", "bt"}
                                  });
    ASSERT_NO_THROW(bankAccountFactory->addAccount());
}

TEST_F(AccountTestInsertShowLoggedIn, emailAccountInsert) {
    const auto emailAccountFactory = AccountFactory::accountFactory(AccountType::EmailAccountType,
    {{"username", "sebi1"},{"password","1234"},
    {"emailAddress", "123412412"}, {"mailProvider", "bt"}});
    ASSERT_NO_THROW(emailAccountFactory->addAccount());
}

TEST_F(AccountTestInsertShowLoggedIn, socialMediaAccountInsert) {
    const auto socialMediaAccountFactory =
    AccountFactory::accountFactory(AccountType::SocialMediaAccountType,
    {{"username", "sebi1"},{"password","1234"},
    {"platform", "123412412"}, {"profileUrl", "bt"}});
    ASSERT_NO_THROW(socialMediaAccountFactory->addAccount());
}

TEST_F(AccountTestInsertShowLoggedIn, bankAccountShow) {
    auto database = DatabasePool::getInstance().acquire();
    const auto accounts = database->getAccountsByType(AccountType::BankAccountType);
    std::streambuf* originalCoutBuffer = std::cout.rdbuf();
    const std::ostringstream capturedOutput;
    std::cout.rdbuf(capturedOutput.rdbuf());
    for (const auto &account : accounts) {
        account->show();
    }
    std::cout.rdbuf(originalCoutBuffer);
    const std::string captured = capturedOutput.str();
    const std::string expectedResult =
R"(---------------------------------
Account details:
Account Type: Bank Account
Username: sebi11
Password: 1234
IBAN: 123412412
Bank: bt
)";
    DatabasePool::getInstance().release(database);
    ASSERT_EQ(captured, expectedResult);
}

TEST_F(AccountTestInsertShowLoggedIn, emailAccountShow) {
    auto database = DatabasePool::getInstance().acquire();
    const auto accounts = database->getAccountsByType(AccountType::EmailAccountType);
    std::streambuf* originalCoutBuffer = std::cout.rdbuf();
    const std::ostringstream capturedOutput;
    std::cout.rdbuf(capturedOutput.rdbuf());
    for (const auto &account : accounts) {
        account->show();
    }
    std::cout.rdbuf(originalCoutBuffer);
    const std::string captured = capturedOutput.str();
    const std::string expectedResult =
R"(---------------------------------
Account details:
Account Type: Email Account
Username: sebi1
Password: 1234
Email Address: 123412412
Mail Provider: bt
)";
    DatabasePool::getInstance().release(database);
    ASSERT_EQ(captured, expectedResult);
}

TEST_F(AccountTestInsertShowLoggedIn, socialMediaAccount) {
    auto database = DatabasePool::getInstance().acquire();
    const auto accounts = database->getAccountsByType(AccountType::SocialMediaAccountType);
    std::streambuf* originalCoutBuffer = std::cout.rdbuf();
    const std::ostringstream capturedOutput;
    std::cout.rdbuf(capturedOutput.rdbuf());
    for (const auto &account : accounts) {
        account->show();
    }
    std::cout.rdbuf(originalCoutBuffer);
    const std::string captured = capturedOutput.str();
    const std::string expectedResult =
R"(---------------------------------
Account details:
Account Type: Social Media Account
Username: sebi1
Password: 1234
Platform: 123412412
Profile URL: bt
)";
    DatabasePool::getInstance().release(database);
    ASSERT_EQ(captured, expectedResult);
}

TEST_F(AccountTestInsertShowLoggedIn, allAccounts) {
    auto database = DatabasePool::getInstance().acquire();
    const auto accounts = database->getAllAccounts();
    std::streambuf* originalCoutBuffer = std::cout.rdbuf();
    const std::ostringstream capturedOutput;
    std::cout.rdbuf(capturedOutput.rdbuf());
    for (const auto &account : accounts) {
        account->show();
    }
    std::cout.rdbuf(originalCoutBuffer);
    const std::string captured = capturedOutput.str();
    const std::string expectedResult =
R"(---------------------------------
Account details:
Account Type: Bank Account
Username: sebi11
Password: 1234
IBAN: 123412412
Bank: bt
---------------------------------
Account details:
Account Type: Email Account
Username: sebi1
Password: 1234
Email Address: 123412412
Mail Provider: bt
---------------------------------
Account details:
Account Type: Social Media Account
Username: sebi1
Password: 1234
Platform: 123412412
Profile URL: bt
)";
    DatabasePool::getInstance().release(database);
    ASSERT_EQ(captured, expectedResult);
}
