// src/cache.hpp
#ifndef CACHE_HPP
#define CACHE_HPP

#include <string>
#include <optional>
#include <boost/multi_index_container.hpp>
#include <boost/multi_index/ordered_index.hpp>

#include "base.hpp"
#include "base_cache.hpp"
#include "CacheMultiIndex.hpp"
#include "cache_eviction_policy.hpp"
#include "cache_item.hpp"

using namespace boost::multi_index;

class Cache : public BaseCache {
public:
    Cache() = default;
    ~Cache() override = default;

    explicit Cache(const std::size_t maxSize, std::unique_ptr<CacheEvictionPolicy> evictionPolicy)
        : maxSize(maxSize), evictionPolicy(std::move(evictionPolicy)) {}

    void put(const std::string& key, const std::string& value, const std::chrono::seconds ttl = std::chrono::seconds(0)) override {
        auto& keyIndex = cacheItems.get<CacheItemIndexes::by_key>();

        // Remove expired items before inserting a new one
        cleanExpiredItems();

        // Если ключ уже существует, обновляем значение
        if (const auto it = keyIndex.find(key); it != keyIndex.end()) {
            keyIndex.modify(it, [&](CacheItem& item) {
                item.value = value;
                item.ttl = ttl; // Update TTL
                item.updateAccessTime();
            });
        } else {
            if (cacheItems.size() >= maxSize) {
                evictionPolicy->evict(cacheItems);
            }
            cacheItems.emplace(CacheItem(key, value, ttl));
        }
    }

    std::optional<std::string> get(const std::string& key) override {
        auto& keyIndex = cacheItems.get<CacheItemIndexes::by_key>();
        cleanExpiredItems(); // Clean expired items before accessing

        if (const auto it = keyIndex.find(key); it != keyIndex.end()) {
            keyIndex.modify(it, [&](CacheItem& item) {
                item.updateAccessTime();
            });
            return it->value;
        }

        return std::nullopt;  // Если ключ не найден
    }

    void remove(const std::string& key) override {
        auto& keyIndex = cacheItems.get<CacheItemIndexes::by_key>();
        keyIndex.erase(key);
    }

    void clear() override {
        cacheItems.clear();
    }
protected:
    std::size_t maxSize;
    CacheMultiIndex cacheItems; // Make cacheItems protected
private:
    void cleanExpiredItems() {
        auto& keyIndex = cacheItems.get<CacheItemIndexes::by_key>();
        for (auto it = keyIndex.begin(); it != keyIndex.end();) {
            if (it->isExpired()) {
                it = keyIndex.erase(it);
            } else {
                ++it;
            }
        }
    }
    std::unique_ptr<CacheEvictionPolicy> evictionPolicy; // Политика эвикции
};

#endif // CACHE_HPP
