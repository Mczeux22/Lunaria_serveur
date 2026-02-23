/**
 * @ Author: Lopapon
 * @ Create Time: 2026-01-26 19:32:20
 * @ Modified by: Lopapon
 * @ Modified time: 2026-02-20 14:52:08
 * @ Description:
 */
#include "server.hpp"

int	main()
{
	asio::io_context io_context;
	Server server(io_context, 2121);
	server.run();
	io_context.run();
	return (0);
}