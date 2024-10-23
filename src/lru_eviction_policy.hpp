//
// Created by massonskyi on 23.10.24.
//

#ifndef LRUEVICTIONPOLICY_HPP
#define LRUEVICTIONPOLICY_HPP
#include "cache_eviction_policy.hpp"
class LRUEvictionPolicy final : public CacheEvictionPolicy {
public:
    void evict(CacheMultiIndex& cache) override {
        if (auto& lastAccessIndex = cache.get<CacheItemIndexes::by_last_access>(); !lastAccessIndex.empty()) {
            lastAccessIndex.erase(lastAccessIndex.begin()); // Удаляем наименее недавно использованный элемент
        }
    }
};
#endif //LRUEVICTIONPOLICY_HPP
