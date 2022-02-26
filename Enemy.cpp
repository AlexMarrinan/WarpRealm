#include "Enemy.h"
#include "EventStep.h"
#include "EventCollision.h"
#include "WorldManager.h"
#include "LogManager.h"

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
		damage_cooldown--;
		if (damage_cooldown < 0) {
			damage_cooldown = 0;
		}
	}
	if (p_e->getType() == df::COLLISION_EVENT) {
		LM.writeLog("Enemy hit");
		const df::EventCollision* ec = dynamic_cast<const df::EventCollision*>(p_e);
		LM.writeLog("%s", ec->getObject1()->getType().c_str());
		LM.writeLog("%s", ec->getObject2()->getType().c_str());
		if ((ec->getObject1()->getType() == "Sword" || ec->getObject2()->getType() == "Sword") && damage_cooldown == 0) {
			this->health--;
			this->damage_cooldown = damage_slowdown;
			if (health <= 0) {
				WM.markForDelete(this);
			}
		}
		return 1;
	}
	return 0;
}
