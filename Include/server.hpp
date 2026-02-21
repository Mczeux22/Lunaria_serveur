#include "header.hpp"

#ifndef SERVER_HPP
#define SERVER_HPP

class	Server
{
	public:
		Server(int port);
		void	run();

	private:
		int port_;
		asio::io_context io;
};

#endif