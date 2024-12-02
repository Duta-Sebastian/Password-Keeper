#include <gtest/gtest.h>
#include <VectorPlusTemplate.cpp>
#include <Account.h>
#include <memory>

#include "AccountFactory.h"

TEST(VectorPlusTest, IntTest) {
    const std::vector v = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    const std::vector v1 = {11, 12, 13, 14, 15, 16, 17, 18, 19, 20};
    const std::vector result = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20};
    ASSERT_EQ(v+v1, result);
}

TEST(VectorPlusTest, DoubleTest) {
    const std::vector v = {1.0, 2.0, 3.0, 4.0};
    const std::vector v1 = {5.0, 6.0, 7.0, 8.0};
    const std::vector result = {1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0};
    ASSERT_EQ(v+v1, result);
}

TEST(VectorPlusTest, AccountTest) {
    const auto bankAccountFactory =
        AccountFactory::accountFactory(AccountType::BankAccountType,
                                   {
                                       {"username", "sebi1"}, {"password", "1234"},
                                       {"IBAN", "123412412"}, {"bank", "bt"}
                                      });
    const auto emailAccountFactory = AccountFactory::accountFactory(AccountType::EmailAccountType,
                                    {{"username", "sebi1"},{"password","1234"},
                                    {"IBAN", "123412412"}, {"bank", "bt"}});
    const std::vector v = {bankAccountFactory};
    const std::vector v1 = {emailAccountFactory};
    const std::vector result = {bankAccountFactory, emailAccountFactory};
    ASSERT_EQ(v+v1, result);
}