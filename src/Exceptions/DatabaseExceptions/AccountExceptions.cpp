//
// Created by sebid on 12/1/2024.
//

#include "AccountExceptions.h"

AccountExceptions::AccountExceptions(std::string message) : message(std::move(message)) {}

const char * AccountExceptions::what() const noexcept {
    return message.c_str();
}

AccountTypeExceptions::AccountTypeExceptions(const std::string &message)
    : AccountTypeExceptions(std::move("The account type is incorrect!\n" + message)) {}


