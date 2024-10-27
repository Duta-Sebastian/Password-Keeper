#ifndef PASSWORDHASH_H
#define PASSWORDHASH_H
#include <string>

class PasswordHash {
    std::string hashedPassword;
    std::string salt;
    static std::string generateSalt();
public:
    explicit PasswordHash(const std::string&);
    PasswordHash(const std::string&, const std::string&);
    [[nodiscard]] std::string getPasswordHash() const;

    [[nodiscard]] std::string getPasswordSalt() const;

    friend std::ostream& operator<<(std::ostream&, const PasswordHash&);
};



#endif //PASSWORDHASH_H
