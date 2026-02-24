/**
 * @ Author: Lopapon
 * @ Create Time: 2026-02-23 22:37:24
 * @ Modified by: Lopapon
 * @ Modified time: 2026-02-24 03:55:22
 * @ Description:
 */
#ifndef SERVER_HPP
#define SERVER_HPP

/* Standard Libraries */

#include <iostream> // std::cout, std::cerr
#include <string> // std::string
#include <vector> // std::vector
#include <map> // std::map
#include <set> // std::set
#include <list> // std::list
#include <memory> // std::shared_ptr, std::unique_ptr
#include <algorithm> // std::find, std::sort, std::for_each
#include <cstdlib> // std::rand, std::srand, std::atoi
#include <ctime> // std::time, std::difftime
#include <fstream> // std::ifstream, std::ofstream, std::fstream

/* Asio Library for networking */

#include <boost/asio.hpp> // Asio Library
#include <functional> //Callbacks
#include <chrono> //Time management

/* Multithreading support */

#include <thread> // std::thread
#include <mutex> // std::mutex, lock_guard, unique_lock
#include <atomic> // std::atomic
#include <condition_variable>

/* Error & security */
#include <stdexcept> // std::runtime_error, logic_error
#include <cassert> // assert()
#include <exception> // std::exception

/*Intern Functionality*/

#include <player.hpp>
#include <struct_loot.hpp>

// Class

class Server {
public:
    Server(asio::io_context& io_context, short port);
    void run();

private:
    void accept_connection();

    asio::io_context& io_context_;  // Référence à io_context
    asio::ip::tcp::acceptor acceptor_;
};

#endif // HEADER_H
>>>>>>> c2292b8 (Modification server.hpp)
