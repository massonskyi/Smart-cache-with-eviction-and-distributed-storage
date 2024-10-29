cmake_minimum_required(VERSION 3.29)
project(SEDSCache)

set(CMAKE_CXX_STANDARD 20)

find_package(Boost REQUIRED)
find_package(cpprestsdk REQUIRED)
find_package(Python3 REQUIRED)
if (Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
    link_directories(${Boost_LIBRARY_DIRS})
else()
    message(FATAL_ERROR "Boost not found!")
endif()

if (cpprestsdk_FOUND)
    include_directories(${cpprestsdk_INCLUDE_DIRS})
    link_directories(${cpprestsdk_LIBRARY_DIRS})
else()
    message(FATAL_ERROR "cpprestsdk not found!")
endif()

if (Python3_FOUND)
    message(STATUS "Found Python3: ${Python3_EXECUTABLE}")
else()
    message(FATAL_ERROR "Python3 not found!")
endif()
include_directories(${CMAKE_SOURCE_DIR}/include)

# Add this to your CMakeLists.txt
add_library(local_cache SHARED
        src/cache_item.hpp
        src/base_cache.hpp
        src/cache_eviction_policy.hpp
        src/cache.hpp
        src/lru_eviction_policy.hpp
        src/lfu_eviction_policy.hpp
        src/fifo_eviction_policy.hpp
        src/base.hpp
        src/CacheMultiIndex.hpp
        src/hash_util.hpp
        src/local_cache.cpp
)

set_target_properties(local_cache PROPERTIES
        LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib
)

# Create a library for remote server-client operations
add_library(remote_cache
        src/cache_server.hpp
        src/cache_client.hpp
        src/replication.hpp
        src/distributed_cache.hpp
        src/cache_server_api.hpp
        src/remote_cache.cpp  # Dummy source file
)

set_target_properties(remote_cache PROPERTIES
        LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib
)
# Link the libraries to the main executable
add_executable(SEDSCache main.cpp)

target_link_libraries(local_cache ${Boost_LIBRARIES})
target_link_libraries(remote_cache ${Boost_LIBRARIES} cpprest)
target_link_libraries(SEDSCache local_cache remote_cache)