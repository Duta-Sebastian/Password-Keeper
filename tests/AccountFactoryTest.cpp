#include <BankAccount.h>
#include <EmailAccount.h>
#include <SocialMediaAccount.h>
#include <gtest/gtest.h>

#include <AccountFactory.h>tes

TEST(AccountFactoryTest, BankAccountCreationTest) {
    const auto bankAccountFactory =
        AccountFactory::accountFactory(AccountType::BankAccountType,
                                   {
                                       {"username", "sebi1"}, {"password", "1234"},
                                       {"IBAN", "123412412"}, {"bank", "bt"}
                                      });
    const auto bankAccountManual = BankAccount("sebi1", "1234", "123412412", "bt");
    ASSERT_EQ(bankAccountManual, *std::dynamic_pointer_cast<BankAccount>(bankAccountFactory));
}

TEST(AccountFactoryTest, EmailAccountCreationTest) {
    const auto emailAccountFactory = AccountFactory::accountFactory(AccountType::EmailAccountType,
        {{"username", "sebi1"},{"password","1234"},
        {"IBAN", "123412412"}, {"bank", "bt"}});
    const auto emailAccountManual = EmailAccount("sebi1", "1234", "123412412", "bt");
    ASSERT_EQ(emailAccountManual, *std::dynamic_pointer_cast<EmailAccount>(emailAccountFactory));
}

TEST(AccountFactoryTest, SocialMediaAccountCreationTest) {
    const auto socialMediaAccountFactory =
        AccountFactory::accountFactory(AccountType::SocialMediaAccountType,
        {{"username", "sebi1"},{"password","1234"},
        {"IBAN", "123412412"}, {"bank", "bt"}});
    const auto socialMediaAccountManual = SocialMediaAccount("sebi1", "1234", "123412412", "bt");
    ASSERT_EQ(socialMediaAccountManual, *std::dynamic_pointer_cast<SocialMediaAccount>(socialMediaAccountFactory));
}
