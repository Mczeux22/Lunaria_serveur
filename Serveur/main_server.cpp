/**
 * @ Author: Lopapon
 * @ Create Time: 2026-01-26 19:32:20
 * @ Modified by: Lopapon
 * @ Modified time: 2026-01-28 23:58:45
 * @ Description:
 */

#include "../Include/header.h"

class	server_streaming
{
	private:
		asio::io_context	io_context;
		asio::ip::tcp::acceptor acceptor;
		std::vector<std::shared_ptr<asio::ip::tcp::socket>>client;
	
	public:
	// contructeur qui initialise l'acceptor
	server_streaming()
		:	acceptor(io_context, asio::ip::tcp::endpoint(asio::ip::tcp::v4(), 4242))
		{
			//Constructeur est vide car tout est initialisé dans la liste d'initialisation
		}

		void	start()
		{
			acceptor.listen();
			std::cout << "Serveur en écoute sur le port 4242" << std::endl;
			accept_connection();
			// a ajouter la logique pour accepter les connexions
		}
		void	accept_connection()
		{
			// Cree une nouvelle socket pour le client
			auto socket = std::make_shared<asio::ip::tcp::socket>(io_context);
			
			// Accepte la connexion de ma maniere asynchrome
			acceptor.async_accept
			(
				*socket, [this, socket](const asio::error_code& error)
				{
					if (!error)
					{
						std::cout << "Nouveau client connecté : "
								  << socket->remote_endpoint().address().to_string()
								  << ":" << socket->remote_endpoint().port()
								  << std::endl;
						client.push_back(socket);
						handle_client(socket);
					}
					else
					{
						std::cerr << "Erreur lors de l'acceptation : " << error.message() << std::endl;
					}
					
					// Continue d'accepter d'autre connexions
					accept_connection();
				}
			);
		}
		
		void	handle_client(std::shared_ptr<asio::ip::tcp::socket > socket)
		{
			// buffer pour recevoir les data
			auto	buffer = std::make_shared<std::array<char, 1024>>();

			socket->async_read_some(asio::buffer(*buffer),
				[this, socket, buffer](const asio::error_code& error, std::size_t bytes_transferred)
				{
					if (!error)
					{
						std::string message(buffer->data(), bytes_transferred);
						std::cout << "Message recu :" << message << std::endl;
						
						// repond au client
						std::string response = "Bien recu";
						asio::async_write(*socket, asio::buffer(response),
							[](const asio::error_code& error, std::size_t bytes_transferred)
							{
								if (error)
									std::cerr << "Erreur d'envoie : " << error.message() << std::endl;
							});
						
						// Continue de lire les messages de ce client
						handle_client(socket);
					}
					else
					{
						std::cout << "client disconnect" << std::endl;
					}
				});
		}

		void	run()
		{
			io_context.run();
		}
};

// Utilisation
int	main()
{
	server_streaming serveur; //Cree le serveur (acceptor initialiser)
	serveur.start(); // Lance l'ecoute
	serveur.run(); // boucle infinie qui traite les event
	return (0);
}