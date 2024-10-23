//
// Created by massonskyi on 23.10.24.
//

#ifndef HASH_UTIL_HPP
#define HASH_UTIL_HPP
#include <string>

inline std::size_t hash_key(const std::string& key) {
    constexpr std::hash<std::string> hasher;
    return hasher(key);
}
#endif //HASH_UTIL_HPP
