/**
 * @ Author: Lopapon
 * @ Create Time: 2026-01-26 19:32:20
 * @ Modified by: Lopapon
 * @ Modified time: 2026-02-25 23:20:58
 * @ Description:
 */
#include "server.hpp"

#include "server.hpp"
#include "db.hpp"

int	main()
{
	g_db = new Database("host=localhost dbname=lunaria_db user=postgres password=lunaria");

	if (!g_db->is_connected())
	{
		std::cerr << "[Main] Impossible de se connecter à la DB." << std::endl;
		return (1);
	}
	asio::io_context	io_context;
	Server			server(io_context, 2121);
	server.run();
	io_context.run();
	delete g_db;
	return (0);
}