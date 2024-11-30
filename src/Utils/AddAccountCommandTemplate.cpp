#include "AddAccountCommandTemplate.h"

#include <iostream>

void AddAccountCommandTemplate<AccountType::BankAccountType>::addAccountCommand() {
    std::cout<<"Please enter the account details!\n";
    std::string username, password, IBAN, bank;
    std::cout<<"Username: ";
    std::cin>>username;
    std::cout<<"Password: ";
    std::cin>>password;
    std::cout<<"IBAN: ";
    std::cin>>IBAN;
    std::cout<<"Bank: ";
    std::cin>>bank;
    const auto account = AccountFactory::accountFactory(AccountType::BankAccountType,
            {{"username",username},
            {"password",password},
            {"IBAN",IBAN},
            {"bank",bank}});
    account->addAccount();
    std::cout<<"Account added successfully!\n";
}

void AddAccountCommandTemplate<AccountType::EmailAccountType>::addAccountCommand() {
    std::cout<<"Please enter the account details!\n";
    std::string username, password, emailAddress, mailProvider;
    std::cout<<"Username: ";
    std::cin>>username;
    std::cout<<"Password: ";
    std::cin>>password;
    std::cout<<"Email Address: ";
    std::cin>>emailAddress;
    std::cout<<"Mail Provider: ";
    std::cin>>mailProvider;
    const auto account = AccountFactory::accountFactory(AccountType::EmailAccountType,
            {{"username",username},
            {"password",password},
            {"emailAddress",emailAddress},
            {"mailProvider",mailProvider}});
    account->addAccount();
    std::cout<<"Account added successfully!\n";
}

void AddAccountCommandTemplate<AccountType::SocialMediaAccountType>::addAccountCommand() {
    std::cout<<"Please enter the account details!\n";
    std::string username, password, platform, profileUrl;
    std::cout<<"Username: ";
    std::cin>>username;
    std::cout<<"Password: ";
    std::cin>>password;
    std::cout<<"Platform: ";
    std::cin>>platform;
    std::cout<<"Profile URL: ";
    std::cin>>profileUrl;
    const auto account = AccountFactory::accountFactory(AccountType::SocialMediaAccountType,
            {{"username",username},
            {"password",password},
            {"platform",platform},
            {"profileUrl",profileUrl}});
    account->addAccount();
    std::cout<<"Account added successfully!\n";
}


