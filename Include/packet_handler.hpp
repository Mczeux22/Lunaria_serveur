/**
 * @ Author: Lopapon
 * @ Create Time: 2026-02-25 20:11:01
 * @ Modified by: Lopapon
 * @ Modified time: 2026-02-25 22:59:45
 * @ Description:
 */

#ifndef PACKET_HANDLER_HPP
#define PACKET_HANDLER_HPP

#include <server.hpp>
#include <packet.hpp>
#include <functional>

class	PacketHandler
{
public:
	using SendCallback = std::function<void(std::vector<uint8_t>)>;

	PacketHandler(uint32_t session_id, SendCallback send_fn);

	void		on_data_received(const char* data, std::size_t length);
	uint32_t	get_session_id() const { return session_id_; }

private:
	void	dispatch(PacketType type, const uint8_t* payload, uint16_t length);
	void	handle_login(const uint8_t* payload, uint16_t length);
	void	handle_chat(const uint8_t* payload, uint16_t length);
	void	handle_ping();

	std::vector<uint8_t>	buffer_;
	uint32_t		session_id_;
	SendCallback		send_;
};

#endif