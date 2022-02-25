#include "Sword.h"
#include "EventStep.h"
#include "WorldManager.h"

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
	sword_countdown = SWORD_SLOWDOWN;
	registerInterest(df::STEP_EVENT);
	setSolidness(HARD);
}
int Sword::eventHandler(const Event* p_e) {
	if (p_e->getType() == df::STEP_EVENT) {
		setPosition(h->getPosition()+ offset);
;		sword_countdown--;
		if (sword_countdown <= 0) {
			WM.markForDelete(this);
		}
		return 1;
	}
	return 0;
}