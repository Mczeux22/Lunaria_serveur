/**
 * @ Author: Lopapon
 * @ Create Time: 2026-02-25 20:10:07
 * @ Modified by: Lopapon
 * @ Modified time: 2026-02-25 22:41:34
 * @ Description:
 */

#include <packet_handler.hpp>

PacketHandler::PacketHandler(uint32_t session_id, SendCallback send_fn)
	: session_id_(session_id),
	  send_(send_fn)
{}

void	PacketHandler::on_data_received(const char* data, std::size_t length)
{
	buffer_.insert(buffer_.end(), data, data + length);

	while (true)
	{
		if (buffer_.size() < sizeof(PacketHeader))
			break ;

		PacketHeader	header;
		std::memcpy(&header, buffer_.data(), sizeof(PacketHeader));

		if (header.length > MAX_PACKET_SIZE)
		{
			std::cerr << "[PacketHandler] Paquet trop grand, session "
				<< session_id_ << " déconnectée." << std::endl;
			buffer_.clear();
			break ;
		}

		std::size_t	total_size = sizeof(PacketHeader) + header.length;
		if (buffer_.size() < total_size)
			break ;

		const uint8_t*	payload = buffer_.data() + sizeof(PacketHeader);
		dispatch(static_cast<PacketType>(header.type), payload, header.length);
		buffer_.erase(buffer_.begin(), buffer_.begin() + total_size);
	}
}

void	PacketHandler::dispatch(PacketType type, const uint8_t* payload, uint16_t length)
{
	switch (type)
	{
		case PKT_LOGIN:
			handle_login(payload, length);
			break ;
		case PKT_CHAT:
			handle_chat(payload, length);
			break ;
		case PKT_PING:
			handle_ping();
			break ;
		default:
			std::cerr << "[PacketHandler] Type inconnu : 0x"
				<< std::hex << (int)type << std::endl;
			break ;
	}
}

void	PacketHandler::handle_ping()
{
	std::cout << "[PacketHandler] Ping reçu de session "
		<< session_id_ << std::endl;

	// On répond avec un vrai paquet PKT_PONG
	auto	pong = make_packet(PKT_PONG);
	send_(pong);
}

void	PacketHandler::handle_login(const uint8_t* payload, uint16_t length)
{
	if (length < sizeof(PktLogin))
	{
		std::cerr << "[PacketHandler] PKT_LOGIN trop court." << std::endl;
		return ;
	}

	PktLogin	pkt;
	std::memcpy(&pkt, payload, sizeof(PktLogin));
	pkt.username[31] = '\0';
	pkt.password[63] = '\0';

	std::cout << "[Login] Tentative de " << pkt.username << std::endl;
	// TODO : vérification en DB
}

void	PacketHandler::handle_chat(const uint8_t* payload, uint16_t length)
{
	if (length < sizeof(PktChat))
	{
		std::cerr << "[PacketHandler] PKT_CHAT trop court." << std::endl;
		return ;
	}

	PktChat	pkt;
	std::memcpy(&pkt, payload, sizeof(PktChat));
	pkt.message[255] = '\0';

	std::cout << "[Chat] session " << session_id_
		<< " : " << pkt.message << std::endl;
}