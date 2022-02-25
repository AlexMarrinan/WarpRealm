#pragma once
#include "Item.h"

class PowerUp: public Item
{
public:
	PowerUpType type;
	PowerUp(df::Vector position, int id, PowerUpType type);
	void getItem();
};

