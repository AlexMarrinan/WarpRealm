#include "Arrow.h"
#include "EventCollision.h"
#include "WorldManager.h"

Arrow::Arrow(df::Vector direction, df::Vector pos) {
	setPosition(pos);
	setDirection(direction);
	if (getDirection().getX() == 0) {
		setSprite("arrow-v");
		setSpeed(0.25);
	}
	else {
		setSprite("arrow-h");
		setSpeed(0.6);
	}
	setType("Enemy");
	setSolidness(SOFT);
	setDamage(1);
	registerInterest(COLLISION_EVENT);
}
int Arrow::eventHandler(const df::Event* p_e) {
	if (p_e->getType() == COLLISION_EVENT) {
		const EventCollision* p_ec = dynamic_cast<const EventCollision*>(p_e);
		if (p_ec->getObject1()->getType() == "Turret" || p_ec->getObject2()->getType() == "Turret") {
			return 1;
		}
		WM.markForDelete(this);
		return 1;
	}
	return 0;
}