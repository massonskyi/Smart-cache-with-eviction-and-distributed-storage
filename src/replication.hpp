//
// Created by massonskyi on 23.10.24.
//

#ifndef REPLICATION_HPP
#define REPLICATION_HPP
#include "cache.hpp"
#include "cache_client.hpp"
#include <vector>
#include <string>

class ReplicationManager {
public:
    ReplicationManager(const std::vector<std::pair<std::string, std::string>>& replica_endpoints,
                       boost::asio::io_context& io_context) {
        for (const auto&[fst, snd] : replica_endpoints) {
            replicas.emplace_back(io_context, fst, snd);
        }
    }

    void replicate(const std::string& key, const std::string& value) {
        for (auto& replica : replicas) {
            std::string request = "PUT " + key + " " + value;
            replica.send_request(request);
        }
    }
private:
    std::vector<CacheClient> replicas;
};
#endif //REPLICATION_HPP
