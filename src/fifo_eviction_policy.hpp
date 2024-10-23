//
// Created by massonskyi on 23.10.24.
//

#ifndef FIFOEVICTIONPOLICY_HPP
#define FIFOEVICTIONPOLICY_HPP
#include "cache_eviction_policy.hpp"

class FIFOEvictionPolicy final : public CacheEvictionPolicy {
public:
    void evict(CacheMultiIndex& cache) override {
        if (auto& keyIndex = cache.get<CacheItemIndexes::by_key>(); !keyIndex.empty()) {
            keyIndex.erase(keyIndex.begin()); // Удаляем самый старый элемент
        }
    }
};
#endif //FIFOEVICTIONPOLICY_HPP
