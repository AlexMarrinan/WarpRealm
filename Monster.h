#pragma once
#include "Enemy.h"
#include "Portal.h"

class Monster: public Enemy
{
private:
	class Hero* h;
	class Room* room;
	bool moving;
	int move_cooldown;
	int move_slowdown;
public:
	Monster(df::Vector position, df::Vector velocity, int id, class Room* room);
	int eventHandler(const df::Event* p_e);
	void usePortal(Portal* p);
};

