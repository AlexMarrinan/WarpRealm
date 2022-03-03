#pragma once
#include "Item.h"
#include "Hero.h"

class Turret : public Item
{
private:
	Hero* h;
	class Room* room;
	int shoot_countdown;
	int shoot_slowdown;
public:
	Turret(df::Vector position, Room* room);
	int eventHandler(const df::Event* p_e);
	void fire(df::Vector direction);
};

