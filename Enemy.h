#pragma once
#include "Item.h"

class Enemy : public Item
{
private:
	int health;
	int damage;
	int damage_cooldown;
	int damage_slowdown;
public:
	Enemy();
	int getHealth() const;
	void setHealth(int n_health);

	int getDamage() const;
	void setDamage(int n_damage);

	virtual int eventHandler(const df::Event* p_e) override;
};

