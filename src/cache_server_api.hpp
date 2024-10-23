//
// Created by massonskyi on 23.10.24.
//

#ifndef CACHE_SERVER_API_HPP
#define CACHE_SERVER_API_HPP

#include <cpprest/http_listener.h>
#include <cpprest/json.h>
#include <string>
#include "distributed_cache.hpp"

class CacheServerAPI {
public:
    explicit CacheServerAPI(DistributedCache& cache) : cache(cache), listener(U("http://localhost:8080")) {
        listener.support(web::http::methods::GET, [this]<typename T0>(T0 && PH1) { handle_get(std::forward<T0>(PH1)); });
        listener.support(web::http::methods::POST, [this]<typename T0>(T0 && PH1) { handle_post(std::forward<T0>(PH1)); });
        listener.support(web::http::methods::DEL, [this]<typename T0>(T0 && PH1) { handle_delete(std::forward<T0>(PH1)); });
    }

    void open() {
        listener
            .open()
            .then([](){ std::wcout << L"Starting to listen at: http://localhost:8080\n"; })
            .wait();
    }

private:
    void handle_get(const web::http::http_request& request) const {
        // Реализуйте логику получения данных из кэша
        auto json_response = web::json::value::object();
        // Пример: получить кэшированные данные
        for (const auto data = cache.get_cache_data(); const auto&[fst, snd] : data) {
            json_response[fst] = web::json::value::string(snd);
        }
        request.reply(web::http::status_codes::OK, json_response);
    }

    void handle_post(const web::http::http_request& request) const {
        // Реализуйте логику добавления данных в кэш
        request.extract_json().then([=](web::json::value json) {
            auto key = json[U("key")].as_string();
            auto value = json[U("value")].as_string();
            cache.put(key, value, std::chrono::seconds(60)); // Пример с TTL 60 секунд
            request.reply(web::http::status_codes::OK, U("Data added to cache"));
        }).wait();
    }

    void handle_delete(const web::http::http_request& request) const {
        // Реализуйте логику удаления данных из кэша
        const auto key = request.request_uri().path();
        cache.remove(key.substr(1)); // Удаление первого символа ('/')
        request.reply(web::http::status_codes::OK, U("Data removed from cache"));
    }

    DistributedCache& cache;
    web::http::http_listener listener;
};

#endif // CACHE_SERVER_API_HPP
