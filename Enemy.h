#pragma once
#include "Object.h"

class Enemy : public df::Object
{
private:
	int health;
	int damage;
public:
	Enemy();
	int getHealth() const;
	void setHealth(int n_health);

	int getDamage() const;
	void setDamage(int n_damage);

	virtual int eventHandler(const df::Event* p_e) override;
};

