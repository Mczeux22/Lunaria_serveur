/**
 * @ Author: Lopapon
 * @ Create Time: 2026-02-25 20:11:01
 * @ Modified by: Lopapon
 * @ Modified time: 2026-02-25 20:14:52
 * @ Description:
 */

#ifndef PACKET_HANDLER_HPP
#define PACKET_HANDLER_HPP

#include <server.hpp>
#include <packet.hpp>

// ===========================
//  PACKET HANDLER
// ===========================

// Reçoit les données brutes d'une session TCP,
// reconstruit les paquets et appelle la bonne fonction

class	PacketHandler
{
	public:
		PacketHandler(uint32_t session_id);
		void		on_data_received(const char* data, std::size_t length);
		uint32_t	get_session_id() const { return session_id_;
}

private:

	// Dispatch selon le type du paquet
	void	dispatch(PacketType type, const uint8_t* payload, uint16_t length);

	// Handlers par type de paquet
	void	handle_login(const uint8_t* payload, uint16_t length);
	void	handle_chat(const uint8_t* payload, uint16_t length);
	void	handle_ping();

	// Buffer interne pour reconstruire les paquets fragmentés
	std::vector<uint8_t>	buffer_;
	uint32_t		session_id_;
};

#endif