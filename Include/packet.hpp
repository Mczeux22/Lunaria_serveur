/**
 * @ Author: Lopapon
 * @ Create Time: 2026-02-25 20:02:01
 * @ Modified by: Lopapon
 * @ Modified time: 2026-02-25 23:13:17
 * @ Description:
 */
#ifndef PACKET_HPP
#define PACKET_HPP

#include <cstdint>
#include <cstring>
#include <string>
#include <vector>

enum PacketType : uint8_t
{
	// Auth TCP
	PKT_LOGIN		= 0x01,
	PKT_LOGIN_OK		= 0x02,
	PKT_LOGIN_FAIL		= 0x03,

	// Gameplay TCP
	PKT_CHAT		= 0x10,
	PKT_CHANGE_ZONE		= 0x11,
	PKT_ITEM_PICKUP		= 0x12,

	// Gameplay UDP
	PKT_PLAYER_MOVE		= 0x20,
	PKT_PLAYER_ATTACK	= 0x21,
	PKT_WORLD_STATE		= 0x22,

	// Utilitaire
	PKT_PING		= 0xF0,
	PKT_PONG		= 0xF1,
};

// ===========================
//  HEADER D'UN PAQUET
// ===========================

// Structure binaire sur le réseau :
// [1 octet : type][2 octets : taille payload][N octets : payload]

#pragma pack(push, 1)	// Désactive le padding du compilateur

struct	PacketHeader
{
	uint8_t		type;		// Type du paquet (PacketType)
	uint16_t	length;		// Taille du payload en octets
};

// ===========================
//  STRUCTS DES PAQUETS
// ===========================

// PKT_LOGIN (TCP) — Client → Serveur
struct	PktLogin
{
	char	username[32];
	char	password[64];
};

// PKT_LOGIN_OK (TCP) — Serveur → Client
struct	PktLoginOk
{
	uint32_t	session_id;	// ID unique de la session
	uint32_t	player_id;	// ID du joueur en DB
};

// PKT_LOGIN_FAIL (TCP) — Serveur → Client
struct	PktLoginFail
{
	uint8_t	reason;		// 0 = mauvais mdp, 1 = compte inexistant
};

// PKT_PLAYER_MOVE (UDP) — Client → Serveur
struct	PktPlayerMove
{
	uint32_t	session_id;	// Pour identifier le joueur en UDP
	float		x;
	float		y;
	float		velocity_x;
	float		velocity_y;
};

// PKT_PLAYER_ATTACK (UDP) — Client → Serveur
struct	PktPlayerAttack
{
	uint32_t	session_id;
	uint32_t	target_id;	// ID de la cible
	uint8_t		attack_type;	// 0 = mêlée, 1 = sort, 2 = projectile
};

// PKT_WORLD_STATE (UDP) — Serveur → Client
// Taille variable selon le nombre de joueurs visibles
struct	PktWorldStateEntry
{
	uint32_t	player_id;
	float		x;
	float		y;
};

// PKT_CHAT (TCP) — Client → Serveur
struct	PktChat
{
	uint32_t	session_id;
	char		message[256];
};

// PKT_PING / PKT_PONG — pas de payload

#pragma pack(pop)

// ===========================
//  UTILITAIRES
// ===========================

// Constante max pour éviter les paquets malformés
static const uint16_t	MAX_PACKET_SIZE = 1024;

// Serialise un paquet complet (header + payload) dans un buffer
// Utilisation : auto buf = make_packet(PKT_LOGIN, &login_data, sizeof(login_data));
inline std::vector<uint8_t>	make_packet(PacketType type, const void* payload, uint16_t length)
{
	std::vector<uint8_t>	buf(sizeof(PacketHeader) + length);
	PacketHeader		header{type, length};

	std::memcpy(buf.data(), &header, sizeof(PacketHeader));
	if (payload && length > 0)
		std::memcpy(buf.data() + sizeof(PacketHeader), payload, length);
	return (buf);
}

// Surcharge pour les paquets sans payload (ping, pong)
inline std::vector<uint8_t>	make_packet(PacketType type)
{
	return make_packet(type, nullptr, 0);
}

#endif