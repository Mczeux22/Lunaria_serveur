/**
 * @ Author: Lopapon
 * @ Create Time: 2026-01-26 19:32:20
 * @ Modified by: Lopapon
 * @ Modified time: 2026-01-28 22:53:49
 * @ Description:
 */

#include "../Include/header.h"

int	main(void)
{
	
}

class	server_streaming
{
	private:
		asio::io_context:: io_context;
		asio::ip::tcp::acceptor acceptor;
	
	public:
	// contructeur qui initialise l'acceptor
	server_streaming()
		:	acceptor(io_context, asio::ip::tcp::endpoint(asio::ip::tcp::v4(), 4242))
		{
			//Constructeur est vide car tout est initialisé dans la liste d'initialisation
		}

		void	start()
		
};