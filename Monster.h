#pragma once
#include "Enemy.h"

class Monster: public Enemy
{
public:
	Monster(df::Vector position, int id);
};

