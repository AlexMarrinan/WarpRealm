#pragma once
#include "Enemy.h"
#include "Portal.h"

class Grass : public Enemy
{
public:
	Grass(df::Vector position, int id);
	int eventHandler(const df::Event* p_e);
};
