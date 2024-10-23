//
// Created by massonskyi on 23.10.24.
//

#ifndef CACHEEVICTIONPOLICY_HPP
#define CACHEEVICTIONPOLICY_HPP
#include "base.hpp"
#include "CacheMultiIndex.hpp"

class CacheEvictionPolicy {
public:
    virtual void evict(CacheMultiIndex& cache) = 0;
    virtual ~CacheEvictionPolicy() = default;
};

#endif //CACHEEVICTIONPOLICY_HPP
