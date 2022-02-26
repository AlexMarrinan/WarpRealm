#include "Sword.h"
#include "EventStep.h"
#include "WorldManager.h"
#include "LogManager.h"
#include "Enemy.h"

Sword::Sword(Hero* h, RoomDirection direction) {
	this->h = h;
	this->direction = direction;
	setType("Sword");
	if (direction == RoomDirection::UP) {
		setSprite("arrow-v");
		this->offset = Vector(0, -3);
	}
	else if (direction == RoomDirection::DOWN) {
		setSprite("arrow-v");
		this->offset = Vector(0, 3);
	}
	else if (direction == RoomDirection::LEFT) {
		setSprite("arrow-h");
		this->offset = Vector(-4, 0);
	}
	else if (direction == RoomDirection::RIGHT) {
		setSprite("arrow-h");
		this->offset = Vector(4, 0);
	}
	registerInterest(df::COLLISION_EVENT);
	sword_countdown = SWORD_SLOWDOWN;
	registerInterest(df::STEP_EVENT);
	setSolidness(HARD);
	setPosition(h->getPosition() + offset);
}
int Sword::eventHandler(const Event* p_e) {
	if (p_e->getType() == df::STEP_EVENT) {
		WM.moveObject(this, getPosition());
;		sword_countdown--;
		if (sword_countdown <= 0) {
			WM.markForDelete(this);
		}
		return 1;
	}
	if (p_e->getType() == df::COLLISION_EVENT) {
		/*
		LM.writeLog("Sword hit");
		const df::EventCollision* ec = dynamic_cast<const df::EventCollision*>(p_e);
		LM.writeLog("%s", ec->getObject1()->getType().c_str());
		LM.writeLog("%s", ec->getObject2()->getType().c_str());
		Enemy* e;
		if (ec->getObject1()->getType() == "Enemy") {
			e = dynamic_cast<Enemy*>(ec->getObject1());
		}
		else if (ec->getObject2()->getType() == "Enemy") {
			e = dynamic_cast<Enemy*>(ec->getObject2());
		}
		else {
			return 1;
		}
		e->setHealth(e->getHealth() - 1);
		if (e->getHealth() <= 0) {
			WM.markForDelete(e);
		}
		return 1;
		*/
	}
	return 0;
}