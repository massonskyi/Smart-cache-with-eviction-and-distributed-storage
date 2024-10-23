#include <boost/asio.hpp>
#include <iostream>
#include <memory>
#include <thread>
#include <unordered_map>

using boost::asio::ip::tcp;

class CacheServer {
public:
    CacheServer(boost::asio::io_context& io_context, const unsigned short port)
        : acceptor_(io_context, tcp::endpoint(tcp::v4(), port)) {
        do_accept();
    }

private:
    tcp::acceptor acceptor_;
    std::unordered_map<std::string, std::string> cache_;

    void do_accept() {
        acceptor_.async_accept(
            [this](boost::system::error_code ec, tcp::socket socket) {
                if (!ec) {
                    std::make_shared<Session>(std::move(socket), cache_)->start();
                } else {
                    std::cerr << "Accept error: " << ec.message() << std::endl;
                }
                do_accept();
            });
    }

    class Session : public std::enable_shared_from_this<Session> {
    public:
        Session(tcp::socket socket, std::unordered_map<std::string, std::string>& cache)
            : socket_(std::move(socket)), cache_(cache) {}

        void start() {
            do_read();
        }

    private:
        tcp::socket socket_;
        std::unordered_map<std::string, std::string>& cache_;
        char data_[1024];

        void do_read() {
            auto self(shared_from_this());
            socket_.async_read_some(boost::asio::buffer(data_),
                [this, self](const boost::system::error_code &ec, const std::size_t length) {
                    if (!ec) {
                        const std::string received_data(data_, length);
                        std::cout << "Received: " << received_data << std::endl;

                        // Здесь вы можете обрабатывать данные, например, обновить кэш
                        // или добавить логику для проверки статуса кэша.

                        std::string response = "Data received successfully!";
                        do_write(response);
                    }
                });
        }

        void do_write(const std::string& response) {
            auto self(shared_from_this());
            boost::asio::async_write(socket_, boost::asio::buffer(response),
                [this, self](boost::system::error_code ec, std::size_t /*length*/) {
                    if (!ec) {
                        do_read();
                    } else {
                        std::cerr << "Write error: " << ec.message() << std::endl;
                    }
                });
        }
    };
};
