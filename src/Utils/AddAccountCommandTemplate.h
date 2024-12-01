#ifndef ADDACCOUNTCOMMANDTEMPLATE_H
#define ADDACCOUNTCOMMANDTEMPLATE_H

#include <AccountFactory.h>

template<AccountType>
class AddAccountCommandTemplate {
public:
    virtual void addAccountCommand() = 0;

    virtual ~AddAccountCommandTemplate() = default;
};

template<>
class AddAccountCommandTemplate<AccountType::BankAccountType> {
public:
    static void addAccountCommand();
};

template<>
class AddAccountCommandTemplate<AccountType::EmailAccountType> {
public:
    static void addAccountCommand();
};

template<>
class AddAccountCommandTemplate<AccountType::SocialMediaAccountType> {
public:
    static void addAccountCommand();
};

#endif //ADDACCOUNTCOMMANDTEMPLATE_H
