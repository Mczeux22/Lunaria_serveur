/**
 * @ Author: Lopapon
 * @ Create Time: 2026-03-18 13:17:20
 * @ Modified by: Lopapon
 * @ Modified time: 2026-03-18 13:55:27
 * @ Description:
 */
#ifndef PLAYER_MANAGER_HPP
#define PLAYER_MANAGER_HPP

#include "player.hpp"
#include "db.hpp"

class	PlayerManager
{
	public:
		//charge la db pour recup les infos joueurs
		static	bool load_player(int account_id, Player& out_player);
		// charge les sorts de la classe
		static	bool load_spells(int account_id, );
		// Sauvegarde la position et les stats en DB
}

#endif