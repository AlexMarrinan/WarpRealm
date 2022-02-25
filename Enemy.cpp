#include "Enemy.h"
#include "EventCollision.h"
#include "WorldManager.h"

Enemy::Enemy() {
	setType("Enemy");
	registerInterest(df::COLLISION_EVENT);
}

int Enemy::getHealth() const {
	return health;
}
void Enemy::setHealth(int n_health) {
	health = n_health;
}

int Enemy::getDamage() const {
	return damage;
}
void Enemy::setDamage(int n_damage) {
	damage = n_damage;
}
int Enemy::eventHandler(const df::Event* p_e)  {
	if (p_e->getType() == df::COLLISION_EVENT) {
		const df::EventCollision* ec = dynamic_cast<const df::EventCollision*>(p_e);
		if (ec->getObject1()->getType() == "Sword" || ec->getObject2()->getType() == "Sword") {
			this->health--;
			if (health <= 0) {
				WM.markForDelete(this);
			}
		}
		return 1;
	}
	return 0;
}
