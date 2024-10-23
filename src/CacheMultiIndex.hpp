//
// Created by massonskyi on 23.10.24.
//

#ifndef CACHEMULTIINDEX_HPP
#define CACHEMULTIINDEX_HPP
#include <boost/multi_index_container.hpp>
#include <boost/multi_index/member.hpp>

#include "base.hpp"
#include "cache_item.hpp"
// Тип кэша на основе Boost.MultiIndex
using CacheMultiIndex = boost::multi_index_container<
    CacheItem,
    boost::multi_index::indexed_by<
        // Индекс по ключу
        boost::multi_index::ordered_unique<
            boost::multi_index::tag<CacheItemIndexes::by_key>,
            boost::multi_index::member<CacheItem, std::string, &CacheItem::key>
        >,
        // Индекс по времени последнего доступа
        boost::multi_index::ordered_non_unique<
            boost::multi_index::tag<CacheItemIndexes::by_last_access>,
            boost::multi_index::member<CacheItem, std::chrono::time_point<std::chrono::steady_clock>, &CacheItem::lastAccessTime>
        >,
        // Индекс по количеству обращений
        boost::multi_index::ordered_non_unique<
            boost::multi_index::tag<CacheItemIndexes::by_access_count>,
            boost::multi_index::member<CacheItem, int, &CacheItem::accessCount>
        >
    >
>;
#endif //CACHEMULTIINDEX_HPP
