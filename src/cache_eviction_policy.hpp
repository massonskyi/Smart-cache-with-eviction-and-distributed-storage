//
// Created by massonskyi on 23.10.24.
//

#ifndef CACHEEVICTIONPOLICY_HPP
#define CACHEEVICTIONPOLICY_HPP
#include "cache.hpp"

class cache_eviction_policy {
public:
    virtual void evict(Cache& cache) = 0;
    virtual ~cache_eviction_policy() = default;
};

#endif //CACHEEVICTIONPOLICY_HPP
