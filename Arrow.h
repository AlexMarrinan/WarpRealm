#pragma once
#include "Enemy.h"
#include "Room.h"

class Arrow : public Enemy
{

private:
	//Portal* blue_portal;
	//Portal* red_portal;
	Room* room;
public:
	Arrow(df::Vector direction, df::Vector pos, Room* room);
	int eventHandler(const df::Event* p_e) override;
	void usePortal(Portal* p);
};

