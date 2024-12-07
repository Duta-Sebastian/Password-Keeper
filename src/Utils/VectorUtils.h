#ifndef VECTORUTILS_H
#define VECTORUTILS_H

#include <vector>

template<typename T>
std::vector<T> operator+(const std::vector<T> &lhs, const std::vector<T> &rhs){
    std::vector<T> result;
    result.reserve(lhs.size() + rhs.size());
    result.insert(result.end(), lhs.begin(), lhs.end());
    result.insert(result.end(), rhs.begin(), rhs.end());
    return result;
}

#endif //VECTORUTILS_H
