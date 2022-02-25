#pragma once
#include "Object.h"
#include "Hero.h"
#include "Event.h"

#define SWORD_SLOWDOWN 15

class Sword : public df::Object
{
	Hero* h;
	RoomDirection direction;
	int sword_countdown;
	df::Vector offset;
public:
	Sword(Hero* h, RoomDirection direction);
	int eventHandler(const Event* p_e);
};

