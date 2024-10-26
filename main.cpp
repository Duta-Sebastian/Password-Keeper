#include <iostream>
#include <array>
#include <pqxx/pqxx>

int main() {
    pqxx::connection c{"dbname=password_keeper user=user password=temp host=localhost port=5433"};
    std::cout<<"Connection secured";
    return 0;
}
