/**
 * @ Author: Lopapon
 * @ Create Time: 2026-02-23 22:35:05
 * @ Modified by: Lopapon
 * @ Modified time: 2026-02-24 03:54:36
 * @ Description:
 */
#include <server.hpp>

Server	server::run()
{
	io_context	io;
	tcp::acceptor acceptor(io, tcp::endpoint(tcp::v4(), 2121)); // lance l'ecoute du port 2121
	std::cout << "Serveur en attente" << std::endl;
}

int	main()
{
	server_initialisation();
}