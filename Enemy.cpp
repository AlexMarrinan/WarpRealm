#include "Enemy.h"
#include "EventCollision.h"

Enemy::Enemy() {
	setType("Enemy");
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
	return 0;
}
