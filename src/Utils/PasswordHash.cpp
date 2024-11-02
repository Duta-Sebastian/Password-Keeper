#include "PasswordHash.h"

#include <random>
#include <string>
#include <digestpp.hpp>
#include <utility>

PasswordHash::PasswordHash(const std::string &password)
    : salt(generateSalt()) {
    hashedPassword = hashPasswordWithSalt(password);
}

bool PasswordHash::operator==(const PasswordHash & other) const {
    return this->hashedPassword == other.hashedPassword && this->salt == other.salt;
}

PasswordHash::PasswordHash(const std::string &password, std::string passwordSalt, const bool generateHash)
    : salt(std::move(passwordSalt)) {
    if(generateHash)
        hashedPassword = hashPasswordWithSalt(password);
    else hashedPassword = password;
}

std::ostream &operator<<(std::ostream &os, const PasswordHash &hashedPassword) {
    os << hashedPassword.salt << hashedPassword.hashedPassword;
    return os;
}

std::string PasswordHash::generateSalt() {
    std::random_device rd;
    std::mt19937 generator(rd());
    std::uniform_int_distribution distribution(0, 255);

    std::string salt;
    for (size_t i = 0; i < 16; ++i) {
        const auto byte = static_cast<unsigned char>(distribution(generator));
        salt += "0123456789abcdef"[byte >> 4];
        salt += "0123456789abcdef"[byte & 0x0f];
    }

    return salt;
}

std::string PasswordHash::getPasswordHash() const {
    return this->hashedPassword;
}

std::string PasswordHash::getPasswordSalt() const {
    return this->salt;
}

std::string PasswordHash::hashPasswordWithSalt(const std::string & password) const {
    const auto passwordWithSalt = password + salt;
    return digestpp::sha512().absorb(passwordWithSalt).hexdigest();
}
