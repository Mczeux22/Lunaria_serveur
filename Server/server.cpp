/**
 * @ Author: Lopapon
 * @ Create Time: 2026-02-23 22:37:24
 * @ Modified by: Lopapon
 * @ Modified time: 2026-02-25 20:12:59
 * @ Description:
 */
#include "server.hpp"
#include "packet_handler.hpp"

// ===========================
//  SESSION
// ===========================

// Chaque session reçoit un ID unique généré à la connexion
static uint32_t	next_session_id = 1;

Session::Session(tcp::socket socket)
	: socket_(std::move(socket)),
	  handler_(next_session_id++),
	  session_id_(handler_.get_session_id())
{}

void	Session::start()
{
	std::cout << "[Session " << session_id_ << "] Client connecté : "
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
				// On passe les données brutes au PacketHandler
				// C'est lui qui reconstruit et dispatch les paquets
				handler_.on_data_received(data_, length);
				do_read();
			}
			else
			{
				std::cout << "[Session " << session_id_
					<< "] Client déconnecté." << std::endl;
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