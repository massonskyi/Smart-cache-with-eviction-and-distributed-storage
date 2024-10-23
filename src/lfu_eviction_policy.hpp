//
// Created by massonskyi on 23.10.24.
//

#ifndef LFUEVICTIONPOLICY_HPP
#define LFUEVICTIONPOLICY_HPP
#include "cache_eviction_policy.hpp"

class LFUEvictionPolicy final : public CacheEvictionPolicy {
public:
    void evict(CacheMultiIndex& cache) override {
        if (auto& accessCountIndex = cache.get<CacheItemIndexes::by_access_count>(); !accessCountIndex.empty()) {
            accessCountIndex.erase(accessCountIndex.begin()); // Удаляем наименее часто используемый элемент
        }
    }
};
#endif //LFUEVICTIONPOLICY_HPP
