#include <boost/asio.hpp>
#include <iostream>
#include <thread>
#include <memory>
#include <vector>
#include "src/cache_server.hpp"
#include "src/cache_client.hpp"
#include "src/distributed_cache.hpp"
#include "src/lru_eviction_policy.hpp"
#include "src/replication.hpp"

void run_client(const std::string& host, const std::string& port, const DistributedCache& cache) {
    try {
        boost::asio::io_context client_context;
        CacheClient client(client_context, host, port);

        // Отправляем кэш и его статус на сервер
        client.send_cache(cache.get_cache_data());  // Предполагается, что есть метод get_cache_data
    } catch (const std::exception& e) {
        std::cerr << "Client exception: " << e.what() << std::endl;
    }
}

int main() {
    try {
        boost::asio::io_context io_context;

        // Настройки реплик
        const std::vector<std::pair<std::string, std::string>> replica_endpoints = {
            {"127.0.0.1", "12345"}, {"127.0.0.1", "12346"}
        };

        // Менеджер репликации
        ReplicationManager replicationManager(replica_endpoints, io_context);

        // Создаем распределенный кэш с репликацией
        std::unique_ptr<CacheEvictionPolicy> lruPolicy = std::make_unique<LRUEvictionPolicy>();
        DistributedCache cache(10, std::move(lruPolicy), replicationManager);

        cache.put("key1", "value1", std::chrono::seconds(10)); // Этот элемент истечет через 10 секунд
        cache.put("key2", "value2", std::chrono::seconds(30)); // Этот элемент истечет через 30 секунд

        // Запускаем сервер кэша в отдельном потоке
        std::thread server_thread([&io_context]() {
            try {
                std::cout << "Starting server on port 12345..." << std::endl;
                CacheServer server1(io_context, 12345);

                std::cout << "Starting replica server on port 12346..." << std::endl;
                CacheServer server2(io_context, 12346);
                io_context.run(); // Запускаем серверный контекст
            } catch (const std::exception& e) {
                std::cerr << "Server exception: " << e.what() << std::endl;
            }
        });

        // Даем серверу время на запуск
        std::this_thread::sleep_for(std::chrono::seconds(2)); // Даем серверу время на запуск

        // Теперь создаем клиента в отдельном потоке
        std::thread client_thread(run_client, "127.0.0.1", "12345", std::ref(cache));

        // Ожидание завершения потоков
        client_thread.join();
        server_thread.join(); // Убедитесь, что подождали завершения потока сервера

    } catch (const std::exception& e) {
        std::cerr << "Exception: " << e.what() << std::endl;
    }

    return 0;
}
