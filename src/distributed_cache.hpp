// src/distributed_cache.hpp
#ifndef DISTRIBUTED_CACHE_HPP
#define DISTRIBUTED_CACHE_HPP

#include "cache.hpp"
#include "replication.hpp"
#include <utility>

class DistributedCache final : public Cache {
public:
    DistributedCache(const std::size_t maxSize, std::unique_ptr<CacheEvictionPolicy> evictionPolicy,
                     ReplicationManager replicationManager)
        : Cache(maxSize, std::move(evictionPolicy)), replicationManager(std::move(replicationManager)) {}

    // Implementing put with TTL
    void put(const std::string& key, const std::string& value, const std::chrono::seconds ttl) override {
        Cache::put(key, value, ttl); // Call the base class put method
        replicationManager.replicate(key, value);
    }
    // Получение данных кэша для отправки клиенту
    [[nodiscard]] std::unordered_map<std::string, std::string> get_cache_data() const {
        std::unordered_map<std::string, std::string> data;

        for (auto& keyIndex = cacheItems.get<CacheItemIndexes::by_key>(); const auto& item : keyIndex) {
            if (!item.isExpired()) {  // Avoid expired items
                data[item.key] = item.value;
            }
        }
        return data;  // Возврат данных кэша
    }
    // Implementing get
    std::optional<std::string> get(const std::string& key) override {
        return Cache::get(key); // Call the base class get method
    }

    // Implementing remove
    void remove(const std::string& key) override {
        Cache::remove(key); // Call the base class remove method
    }

    // Implementing clear
    void clear() override {
        Cache::clear(); // Call the base class clear method
    }

private:
    ReplicationManager replicationManager;
};

#endif // DISTRIBUTED_CACHE_HPP
