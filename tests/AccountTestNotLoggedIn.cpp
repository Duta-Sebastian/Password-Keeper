#include <gtest/gtest.h>
#include <AccountFactory.h>

TEST(AccountTest, noBankAccountCreatedWhenNotLoggedIn) {
    const auto bankAccountFactory =
        AccountFactory::accountFactory(AccountType::BankAccountType,
                                   {
                                       {"username", "sebi1"}, {"password", "1234"},
                                       {"IBAN", "123412412"}, {"bank", "bt"}
                                      });
    ASSERT_THROW(bankAccountFactory->addAccount(), std::exception);
}

TEST(AccountTest, noEmailAccountCreatedWhenNotLoggedIn) {
    const auto emailAccountFactory = AccountFactory::accountFactory(AccountType::EmailAccountType,
                                    {{"username", "sebi1"},{"password","1234"},
                                    {"emailAddress", "123412412"}, {"mailProvider", "bt"}
                                    });
    ASSERT_THROW(emailAccountFactory->addAccount(), std::exception);
}

TEST(AccountTest, noSocialMediaAccountCreatedWhenNotLoggedIn) {
    const auto socialMediaAccountFactory =
        AccountFactory::accountFactory(AccountType::SocialMediaAccountType,
    {{"username", "sebi1"},{"password","1234"},
    {"platform", "123412412"}, {"profileUrl", "bt"}});
    ASSERT_THROW(socialMediaAccountFactory->addAccount(), std::exception);
}