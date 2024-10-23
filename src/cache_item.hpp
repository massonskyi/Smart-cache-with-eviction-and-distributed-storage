//
// Created by massonskyi on 23.10.24.
//

#ifndef СACHE_ITEM_HPP
#define СACHE_ITEM_HPP
#include <chrono>
#include <string>
#include <utility>

class CacheItem final {
public:
    CacheItem() = default;
    CacheItem(std::string  key, std::string  value)
        : key(std::move(key)), value(std::move(value)), accessCount(0) {
        lastAccessTime = std::chrono::steady_clock::now();
    }
    CacheItem(const CacheItem&) = default;
    CacheItem(CacheItem&&) = default;
    CacheItem& operator=(const CacheItem&) = default;

    void updateAccessTime() {
        lastAccessTime = std::chrono::steady_clock::now();
        ++accessCount;
    }

    std::string key;
    std::string value;
    std::chrono::time_point<std::chrono::steady_clock> lastAccessTime;
    int accessCount;
};
#endif //СACHE_ITEM_HPP
