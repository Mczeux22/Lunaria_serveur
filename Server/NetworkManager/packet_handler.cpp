/**
 * @ Author: Lopapon
 * @ Create Time: 2026-02-25 20:10:07
 * @ Modified by: Lopapon
 * @ Modified time: 2026-02-25 20:10:31
 * @ Description:
 */

#include <packet_handler.hpp>

// ===========================
//  CONSTRUCTEUR
// ===========================

PacketHandler::PacketHandler(uint32_t session_id)
	: session_id_(session_id)
{}

// ===========================
//  RECEPTION DES DONNEES
// ===========================

// TCP est un flux continu d'octets.
// Un appel à do_read() peut recevoir :
//   - Un paquet complet
//   - Un morceau de paquet (fragmentation)
//   - Plusieurs paquets d'un coup (coalescing)
//
// On accumule tout dans buffer_ et on traite
// uniquement quand on a un paquet complet.

void	PacketHandler::on_data_received(const char* data, std::size_t length)
{
	// Ajout des nouvelles données dans le buffer
	buffer_.insert(buffer_.end(), data, data + length);

	// Boucle : on traite tous les paquets complets disponibles
	while (true)
	{
		// Pas assez de données pour lire le header
		if (buffer_.size() < sizeof(PacketHeader))
			break ;

		// Lire le header sans consommer le buffer
		PacketHeader	header;
		std::memcpy(&header, buffer_.data(), sizeof(PacketHeader));

		// Vérification de sécurité : paquet trop grand
		if (header.length > MAX_PACKET_SIZE)
		{
			std::cerr << "[PacketHandler] Paquet trop grand, session "
				<< session_id_ << " déconnectée." << std::endl;
			buffer_.clear();
			break ;
		}

		// Pas encore le payload complet, on attend
		std::size_t	total_size = sizeof(PacketHeader) + header.length;
		if (buffer_.size() < total_size)
			break ;

		// Paquet complet — on dispatch
		const uint8_t*	payload = buffer_.data() + sizeof(PacketHeader);
		dispatch(static_cast<PacketType>(header.type), payload, header.length);

		// Supprimer le paquet traité du buffer
		buffer_.erase(buffer_.begin(), buffer_.begin() + total_size);
	}
}

// ===========================
//  DISPATCH
// ===========================

// Redirige vers le bon handler selon le type
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

// ===========================
//  HANDLERS
// ===========================

void	PacketHandler::handle_login(const uint8_t* payload, uint16_t length)
{
	if (length < sizeof(PktLogin))
	{
		std::cerr << "[PacketHandler] PKT_LOGIN trop court." << std::endl;
		return ;
	}

	PktLogin	pkt;
	std::memcpy(&pkt, payload, sizeof(PktLogin));

	// Sécurité : forcer le null terminator
	pkt.username[31] = '\0';
	pkt.password[63] = '\0';

	std::cout << "[Login] Tentative de " << pkt.username << std::endl;

	// TODO : vérification en DB ici
	// Pour l'instant on accepte tout le monde
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

void	PacketHandler::handle_ping()
{
	std::cout << "[PacketHandler] Ping reçu de session "
		<< session_id_ << std::endl;
	// TODO : envoyer PKT_PONG en retour via la session
}
