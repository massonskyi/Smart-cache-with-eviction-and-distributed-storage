// src/local_cache.cpp
#include "cache.hpp"
#include "lru_eviction_policy.hpp"
#include "lfu_eviction_policy.hpp"
#include "fifo_eviction_policy.hpp"

extern "C" {
    Cache* Cache_new(std::size_t max_size) {
        return new Cache(max_size, std::make_unique<LRUEvictionPolicy>());
    }

    void Cache_put(Cache* cache, const char* key, const char* value, int ttl) {
        cache->put(key, value, std::chrono::seconds(ttl));
    }

    const char* Cache_get(Cache* cache, const char* key) {
        const auto result = cache->get(key);
        return result ? result->c_str() : nullptr;
    }

    void Cache_remove(Cache* cache, const char* key) {
        cache->remove(key);
    }

    void Cache_clear(Cache* cache) {
        cache->clear();
    }

    LRUEvictionPolicy* LRUEvictionPolicy_new() {
        return new LRUEvictionPolicy();
    }

    LFUEvictionPolicy* LFUEvictionPolicy_new() {
        return new LFUEvictionPolicy();
    }

    FIFOEvictionPolicy* FIFOEvictionPolicy_new() {
        return new FIFOEvictionPolicy();
    }
}