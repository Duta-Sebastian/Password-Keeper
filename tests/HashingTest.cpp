#include <digestpp.hpp>
#include <gtest/gtest.h>

#include "../src/User/User.h"
#include "../src/Utils/PasswordHash.h"

TEST(HashingTest, HashFunctionReturnsExpectedValue) {
    const auto password = "password";
    const auto actualHashedPassword = digestpp::sha512().absorb(password).hexdigest();
    const auto expectedHashedPassword = "b109f3bbbc244eb82441917ed06d618b9008dd09b3befd1b5e07394c706a8bb980b1d7785e5976ec049b46df5f1326af5a2ea6d103fd07c95385ffab0cacbc86";
    ASSERT_EQ(expectedHashedPassword, actualHashedPassword);
}

TEST(HashingTest, SaltGeneratorIsUnique) {
    const auto firstSalt = PasswordHash::generateSalt();
    const auto secondSalt = PasswordHash::generateSalt();
    ASSERT_NE(firstSalt, secondSalt);
}

TEST(HashingTest, TwoUsersWithSamePasswordHaveDifferentHashes) {
    const auto firstUser = User("first", "password");
    const auto secondUser = User("second", "password");
    ASSERT_NE(firstUser.getPasswordHash(), secondUser.getPasswordHash());
}

TEST(HashingTest, PasswordCanBeRehashedUsingSalt) {
    const auto salt = PasswordHash::generateSalt();
    const PasswordHash passwordHash("password", salt);
    const PasswordHash passwordHash2("password", salt);
    ASSERT_EQ(passwordHash.getPasswordHash(), passwordHash2.getPasswordHash());
}