/**
 * @ Author: Lopapon
 * @ Create Time: 2026-02-25 20:02:01
 * @ Modified by: Your name
 * @ Modified time: 2026-02-26 20:12:27
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
	// Auth TC
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

#pragma pack(push, 1)

struct	PacketHeader
{
	uint8_t		type;
	uint16_t	length;	
};

struct	PktLogin
{
	char	username[32];
	char	password[64];
};

struct	PktLoginOk
{
	uint32_t	session_id;
	uint32_t	player_id;
};

struct	PktLoginFail
{
	uint8_t	reason;		// 0 = mauvais mdp, 1 = compte inexistant
};

struct	PktPlayerMove
{
	uint32_t	session_id;	// Pour identifier le joueur en UDP
	float		x;
	float		y;
	float		velocity_x;
	float		velocity_y;
};

struct	PktPlayerAttack
{
	uint32_t	session_id;
	uint32_t	target_id;
	uint8_t		attack_type;
};

struct	PktWorldStateEntry
{
	uint32_t	player_id;
	float		x;
	float		y;
};

struct	PktChat
{
	uint32_t	session_id;
	char		message[256];
};

#pragma pack(pop)

static const uint16_t	MAX_PACKET_SIZE = 1024;

inline std::vector<uint8_t>	make_packet(PacketType type, const void* payload, uint16_t length)
{
	std::vector<uint8_t>	buf(sizeof(PacketHeader) + length);
	PacketHeader		header{type, length};

	std::memcpy(buf.data(), &header, sizeof(PacketHeader));
	if (payload && length > 0)
		std::memcpy(buf.data() + sizeof(PacketHeader), payload, length);
	return (buf);
}

inline std::vector<uint8_t>	make_packet(PacketType type)
{
	return make_packet(type, nullptr, 0);
}

#endif