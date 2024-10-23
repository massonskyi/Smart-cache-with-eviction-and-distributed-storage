// src/cache_item.hpp
#ifndef CACHE_ITEM_HPP
#define CACHE_ITEM_HPP

#include <chrono>
#include <string>
#include <utility>

class CacheItem final {
public:
    CacheItem() = default;
    CacheItem(std::string key, std::string value, std::chrono::seconds ttl = std::chrono::seconds(0))
        : key(std::move(key)), value(std::move(value)), ttl(ttl), accessCount(0) {
        lastAccessTime = std::chrono::steady_clock::now();
    }

    CacheItem(const CacheItem&) = default;
    CacheItem(CacheItem&&) = default;
    CacheItem& operator=(const CacheItem&) = default;

    void updateAccessTime() {
        lastAccessTime = std::chrono::steady_clock::now();
        ++accessCount;
    }

    bool isExpired() const {
        return ttl > std::chrono::seconds(0) &&
               (std::chrono::steady_clock::now() - lastAccessTime) > ttl;
    }

    std::string key;
    std::string value;
    std::chrono::time_point<std::chrono::steady_clock> lastAccessTime;
    int accessCount;
    std::chrono::seconds ttl; // Time-to-Live for the cache item
};

#endif // CACHE_ITEM_HPP
