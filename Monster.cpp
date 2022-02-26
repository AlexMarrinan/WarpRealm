#include "Monster.h"
#include "EventCollision.h"
#include "WorldManager.h"


Monster::Monster(df::Vector position, int id) {
	setType("Enemy");
	setSprite("monster");
	setPosition(position);
	setHealth(3);
	setDamage(2);
	setId(id);
	registerInterest(df::COLLISION_EVENT);
}
