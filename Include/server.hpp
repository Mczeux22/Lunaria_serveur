/**
 * @ Author: Lopapon
 * @ Create Time: 2026-02-23 22:37:24
 * @ Modified by: Your name
 * @ Modified time: 2026-02-26 20:14:21
 * @ Description:
 */
#ifndef SERVER_HPP
#define SERVER_HPP

/* Standard Libraries */
#include <iostream>
#include <string>
#include <memory>
#include <vector>
#include <cstdint>

/* Boost Asio */
#include <boost/asio.hpp>

namespace asio = boost::asio;
using tcp = boost::asio::ip::tcp;

/* Intern Functionality */
#include <player.hpp>
#include <struct_loot.hpp>

class PacketHandler;

class Session : public std::enable_shared_from_this<Session>
{
public:
	Session(tcp::socket socket);
	void	start();

private:
	void	do_read();

	tcp::socket			socket_;
	char				data_[1024];
	std::unique_ptr<PacketHandler>	handler_;
	uint32_t			session_id_;
};

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