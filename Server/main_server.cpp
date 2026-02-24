/**
 * @ Author: Lopapon
 * @ Create Time: 2026-01-26 19:32:20
 * @ Modified by: Lopapon
 * @ Modified time: 2026-02-24 03:53:36
 * @ Description:
 */
#include "server.hpp"

int	server_initialisation()
{
	asio::io_context io_context;
	Server server(io_context, 2121);
	server.run();
	io_context.run();
	return (0);
}