#include "PasswordHash.h"

#include <random>
#include <crypt.h>
#include <string>
#include <iomanip>

PasswordHash::PasswordHash(const std::string& password) {
    salt = generateSalt();
    hashedPassword = crypt(password.c_str(), salt.c_str());
}

PasswordHash::PasswordHash(const std::string& password, const std::string& passwordSalt) {
    salt = passwordSalt;
    hashedPassword = crypt(password.c_str(), salt.c_str());
}


std::ostream& operator<<(std::ostream& os, const PasswordHash& hashedPassword) {
    os << hashedPassword.salt << hashedPassword.hashedPassword;
    return os;
}

std::string PasswordHash::generateSalt() {
    std::random_device rd;
    std::mt19937 generator(rd());
    std::uniform_int_distribution<int> distribution(0, 255);

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