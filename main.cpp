
#include "header.hpp"

Server	server::run()
{
	io_context	io;
	tcp::acceptor acceptor(io, tcp::endpoint(tcp::v4(), 2121)); // lance l'ecoute du port 2121
	std::cout << "Serveur en attente" << std::endl;
}

int	main(void)
{
	server.port();
	server.run();
}