#ifndef SERVER_HPP
#define SERVER_HPP

/* Standard Libraries */
#include <iostream>
#include <string>
#include <memory>

/* Boost Asio */
#include <boost/asio.hpp>

namespace asio = boost::asio;
using tcp = boost::asio::ip::tcp;

/* Intern Functionality */
#include <player.hpp>
#include <struct_loot.hpp>

// ===== SESSION =====
class Session : public std::enable_shared_from_this<Session>
{
public:
	Session(tcp::socket socket);
	void	start();

private:
	void	do_read();

	tcp::socket	socket_;
	char		data_[1024];
};

// ===== SERVER =====
class Server
{
public:
	Server(asio::io_context& io_context, short port);
	void	run();

private:
	void	accept_connection();

	asio::io_context&	io_context_;
	tcp::acceptor		acceptor_;
};

#endif