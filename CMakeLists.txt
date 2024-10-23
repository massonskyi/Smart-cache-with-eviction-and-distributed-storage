cmake_minimum_required(VERSION 3.29)
project(SEDSCache)

set(CMAKE_CXX_STANDARD 20)

find_package(Boost REQUIRED)

if (Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
    link_directories(${Boost_LIBRARY_DIRS})
else()
    message(FATAL_ERROR "Boost not found!")
endif()
find_package(cpprestsdk REQUIRED)
if (cpprestsdk_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
    link_directories(${Boost_LIBRARY_DIRS})
else()
    message(FATAL_ERROR "Boost not found!")
endif()


include_directories(${Boost_INCLUDE_DIRS})

include_directories(${CMAKE_SOURCE_DIR}/include)

add_executable(
        SEDSCache
        main.cpp
        src/cache_item.hpp
        src/base_cache.hpp
        src/cache_eviction_policy.hpp
        src/cache.hpp
        src/lru_eviction_policy.hpp
        src/lfu_eviction_policy.hpp
        src/fifo_eviction_policy.hpp
        src/base.hpp
        src/CacheMultiIndex.hpp
        src/cache_server.hpp
        src/cache_client.hpp
        src/hash_util.hpp
        src/replication.hpp
        src/distributed_cache.hpp
        src/cache_server_api.hpp
        src/cache_gui.hpp
)

target_link_libraries(SEDSCache ${Boost_LIBRARIES} cpprest)