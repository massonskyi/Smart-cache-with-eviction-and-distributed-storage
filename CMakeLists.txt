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

include_directories(${Boost_INCLUDE_DIRS})

include_directories(${CMAKE_SOURCE_DIR}/include)

add_executable(
        SEDSCache
        main.cpp
        src/cache_item.hpp
        src/cache.hpp
        src/cache_eviction_policy.hpp
)

target_link_libraries(SEDSCache ${Boost_LIBRARIES})