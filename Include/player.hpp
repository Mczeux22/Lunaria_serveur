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
	int	class_id; // 0 admin / 1 mage / 2 guerrier / 3 voleur / 4 chasseur / 5 invocateur
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
	int	armor_type;
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

struct	mage_class
{
	int	class_id; // 1 mage
	int	max_life_mage;
	int	max_mana_mage;
	int	armor_mage;
	int	armor_type_mage;
	float	attack_speed_mage;
	float	attack_range_mage;

	int	magic_power_mage;
	int	strenght_mage;
	int	agility_mage;
	int	intelligence_mage;
	int	resistance_mage;
	int	endurance_mage;
};

struct	warrior_class
{
	int	class_id; // 2 guerrier
	int	max_life_warrior;
	int	max_mana_warrior;
	int	armor_warrior;
	int	armor_type_warrior;
	float	attack_speed_warrior;
	float	attack_range_warrior;

	int	magic_power_warrior;
	int	strenght_warrior;
	int	agility_warrior;
	int	intelligence_warrior;
	int	resistance_warrior;
	int	endurance_warrior;
};

struct	rogue_class
{
	int	class_id; // 3 rogue
	int	max_life_rogue;
	int	max_mana_rogue;
	int	armor_rogue;
	int	armor_type_rogue;
	float	attack_speed_rogue;
	float	attack_range_rogue;

	int	magic_power_rogue;
	int	strenght_rogue;
	int	agility_rogue;
	int	intelligence_rogue;
	int	resistance_rogue;
	int	endurance_rogue;
};

struct	hunter_class
{
	int	class_id; // 4 hunter
	int	max_life_hunter;
	int	max_mana_hunter;
	int	armor_hunter;
	int	armor_type_hunter;
	float	attack_speed_hunter;
	float	attack_range_hunter;

	int	magic_power_hunter;
	int	strenght_hunter;
	int	agility_hunter;
	int	intelligence_hunter;
	int	resistance_hunter;
	int	endurance_hunter;
};

struct	invocator_class
{
	int	class_id; // 5 invocator
	int	max_life_invocator;
	int	max_mana_invocator;
	int	armor_invocator;
	int	armor_type_invocator;
	float	attack_speed_invocator;
	float	attack_range_invocator;

	int	magic_power_invocator;
	int	strenght_invocator;
	int	agility_invocator;
	int	intelligence_invocator;
	int	resistance_invocator;
	int	endurance_invocator;
};

#endif