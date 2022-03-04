#include "Sword.h"
#include "EventStep.h"
#include "WorldManager.h"
#include "LogManager.h"
#include "Enemy.h"
#include "ResourceManager.h"

Sword::Sword(Hero* h, RoomDirection direction) {
	this->h = h;
	this->direction = direction;
	setType("Sword");
	if (direction == RoomDirection::UP) {
		setSprite("sword-u");
		this->offset = Vector(0, -2);
	}
	else if (direction == RoomDirection::DOWN) {
		setSprite("sword-d");
		this->offset = Vector(0, 2);
	}
	else if (direction == RoomDirection::LEFT) {
		setSprite("sword-l");
		this->offset = Vector(-4, 0);
	}
	else if (direction == RoomDirection::RIGHT) {
		setSprite("sword-r");
		this->offset = Vector(4, 0);
	}
	df::Sound* p_sound = RM.getSound("sword-slash");
	p_sound->play();
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
	return 0;
}