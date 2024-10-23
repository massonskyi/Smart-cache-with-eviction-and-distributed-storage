#ifndef CACHE_CLIENT_HPP
#define CACHE_CLIENT_HPP

#include <boost/asio.hpp>
#include <iostream>
#include <memory>

using boost::asio::ip::tcp;

class CacheClient {
public:
    CacheClient(boost::asio::io_context& io_context, const std::string& host, const std::string& port)
        : resolver_(std::make_shared<tcp::resolver>(io_context)),
          socket_(std::make_shared<tcp::socket>(io_context)) {
        do_connect(host, port);
    }

    // Copy constructor
    CacheClient(const CacheClient& other)
        : resolver_(other.resolver_), socket_(other.socket_) {}

    // Copy assignment operator
    CacheClient& operator=(const CacheClient& other) {
        if (this == &other) {
            return *this;
        }
        resolver_ = other.resolver_;
        socket_ = other.socket_;
        return *this;
    }
    void send_cache(const std::unordered_map<std::string, std::string>& cache) const {
        std::string cache_data;
        for (const auto& [key, value] : cache) {
            cache_data += key + ": " + value + "\n";
        }
        send_request(cache_data);
    }
    void send_request(const std::string& request) const {
        try {
            if (!socket_->is_open()) {
                std::cerr << "Socket is not open, cannot send request." << std::endl;
                return;
            }
            boost::asio::write(*socket_, boost::asio::buffer(request));
        } catch (const boost::system::system_error& e) {
            std::cerr << "Failed to send request: " << e.what() << std::endl;
        }
    }
private:
    std::shared_ptr<tcp::resolver> resolver_;
    std::shared_ptr<tcp::socket> socket_;

    void do_connect(const std::string& host, const std::string& port) const {
        try {
            const auto endpoints = resolver_->resolve(host, port);
            boost::asio::connect(*socket_, endpoints);
            std::cout << "Successfully connected to " << host << ":" << port << std::endl;
        } catch (const boost::system::system_error& e) {
            std::cerr << "Failed to connect: " << e.what() << std::endl;
        }
    }
};
#endif //CACHE_CLIENT_HPP
