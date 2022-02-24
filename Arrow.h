#pragma once
#include "Enemy.h"
#include "Room.h"

class Arrow : public Enemy
{
public:
	Arrow(df::Vector direction, df::Vector pos);
	int eventHandler(const df::Event* p_e) override;
};

