// src/main.cpp
#include <iostream>
#include "src/cache_item.hpp"
#include "src/cache.hpp"
#include "src/cache_eviction_policy.hpp"

int main() {
    std::cout << "Smart Cache Project Initialized!" << std::endl;

    // Тестовый объект кэша
    CacheItem item("test_key", "test_value");
    std::cout << "CacheItem created with key: " << item.key << " and value: " << item.value << std::endl;

    // Обновляем время доступа
    item.updateAccessTime();
    std::cout << "CacheItem updated, access count: " << item.accessCount << std::endl;

    return 0;
}
