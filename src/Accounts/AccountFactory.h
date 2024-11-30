//
// Created by sebid on 11/30/2024.
//

#ifndef ACCOUNTFACTORY_H
#define ACCOUNTFACTORY_H

#include <map>
#include <memory>
#include <vector>

#include "Account.h"

class AccountFactory {
public:
    static std::shared_ptr<Account> accountFactory(AccountType, std::map<std::string, std::string>);
};



#endif //ACCOUNTFACTORY_H
