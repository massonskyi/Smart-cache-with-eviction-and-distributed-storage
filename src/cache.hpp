//
// Created by massonskyi on 23.10.24.
//

#ifndef CACHE_H
#define CACHE_H
#include <string>
#include <optional>

class Cache {
public:
    virtual void put(const std::string& key, const std::string& value)  = 0;
    virtual std::optional<std::string> get(const std::string& key) = 0;
    virtual std::optional<std::string> get(const std::string& key) = 0;
    virtual void remove(const std::string& key) = 0;
    virtual void clear() = 0;
    virtual ~Cache() = default;
};
#endif //CACHE_H
