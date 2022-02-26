#pragma once
#include "Item.h"

class Enemy : public Item
{
private:
	int health;
	int damage;
	int damage_slowdown;
public:
	int damage_cooldown;
	Enemy();
	int getHealth() const;
	void setHealth(int n_health);

	int getDamage() const;
	void setDamage(int n_damage);
	void takeDamage(int damage);

	virtual int eventHandler(const df::Event* p_e) override;
};

