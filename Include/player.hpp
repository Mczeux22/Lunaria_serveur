/**
 * @ Author: Lopapon
 * @ Create Time: 2026-02-21 21:16:46
 * @ Modified by: Your name
 * @ Modified time: 2026-02-26 20:13:18
 * @ Description:
 */

#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "server.hpp"

struct	player
{
	// Infomation player
	int	account_id;
	char	*name;
	float	pos_x;
	float	pos_y;
	float	velocity_x;
	float	velocity_y;
	float	speed;

	//Stats player

	int	max_life;
	int	life;
	int	max_mana;
	int	mana;
	int	armor;
	int	level;
	int	max_level;
	int	current_exp;
	float	attack_speed;
	float	attack_range;

	int	magic_power; // Puissance des sorts
	int	strenght; // Force au corps a corps
	int	agility; // Taux de critique au corps a corps
	int	intelligence; // Taux de critiques des sorts
	int	resistance; // Augmente la resistance globale
	int	endurance; // Augmente les points de vie
};

#endif