#include "Enemy.h"
#include "EventStep.h"
#include "EventCollision.h"
#include "WorldManager.h"
#include "LogManager.h"
#include "EventView.h"
#include "HealthDisplay.h"
Enemy::Enemy() {
	setType("Enemy");
	registerInterest(df::COLLISION_EVENT);
	registerInterest(df::STEP_EVENT);
	damage_cooldown = 0;
	damage_slowdown = 15;
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
	if (p_e->getType() == df::STEP_EVENT) {
		WM.moveObject(this, getPosition());
		damage_cooldown--;
		if (damage_cooldown < 0) {
			damage_cooldown = 0;
		}
		return 1;
	}
	return 0;
}
void Enemy::takeDamage(int damage) {
	this->health--;
	this->damage_cooldown = damage_slowdown;
}
