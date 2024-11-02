#ifndef PASSWORDHASH_H
#define PASSWORDHASH_H
#include <string>

class PasswordHash {
    std::string hashedPassword;
    std::string salt;
public:
    explicit PasswordHash(const std::string&);
    PasswordHash(const std::string&, std::string );
    [[nodiscard]] std::string getPasswordHash() const;

    [[nodiscard]] std::string getPasswordSalt() const;

    [[nodiscard]] std::string hashPasswordWithSalt(const std::string&) const;

    static std::string generateSalt();

    friend std::ostream& operator<<(std::ostream&, const PasswordHash&);
};



#endif //PASSWORDHASH_H
