/**
 * @ Author: Lopapon
 * @ Create Time: 2026-02-20 14:41:42
 * @ Modified by: Lopapon
 * @ Modified time: 2026-02-25 18:46:11
 * @ Description:
 */

#include "server.hpp"

// ===========================
//  SESSION
// ===========================

Session::Session(tcp::socket socket)
	: socket_(std::move(socket))
{}

void	Session::start()
{
	std::cout << "[Session] Client connecté : "
		<< socket_.remote_endpoint().address().to_string()
		<< std::endl;
	do_read();
}

void	Session::do_read()
{
	auto self = shared_from_this();

	socket_.async_read_some(
		asio::buffer(data_, sizeof(data_)),
		[this, self](boost::system::error_code ec, std::size_t length)
		{
			if (!ec)
			{
				std::string	message(data_, length);
				std::cout << "[Reçu] " << message << std::endl;

				std::string	response = "pong\n";
				asio::async_write(socket_,
					asio::buffer(response),
					[](boost::system::error_code, std::size_t){});

				do_read();
			}
			else
			{
				std::cout << "[Session] Client déconnecté." << std::endl;
			}
		}
	);
}

// ===========================
//  SERVER
// ===========================

Server::Server(asio::io_context& io_context, short port)
	: io_context_(io_context),
	  acceptor_(io_context, tcp::endpoint(tcp::v4(), port))
{}

void	Server::run()
{
	std::cout << "[Serveur] En écoute sur le port "
		<< acceptor_.local_endpoint().port()
		<< std::endl;
	accept_connection();
}

void	Server::accept_connection()
{
	acceptor_.async_accept(
		[this](boost::system::error_code ec, tcp::socket socket)
		{
			if (!ec)
			{
				std::make_shared<Session>(std::move(socket))->start();
			}
			accept_connection();
		}
	);
}
