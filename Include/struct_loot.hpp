/**
 * @ Author: Lopapon
 * @ Create Time: 2026-01-28 22:23:20
 * @ Modified by: Your name
 * @ Modified time: 2026-02-21 00:50:07
 * @ Description:
 */

#include "header.hpp"

#ifndef LOOT_H
#define LOOT_H

struct	ItemTemplate
{
	int	id;
	std::string name;
	int	rarity;
};

struct	LootResult
{
	int	item_id;
	int	quantity;
};

#endif // LOOT_H