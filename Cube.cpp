#include "Cube.h"
#include "Object.h"
#include "EventCollision.h"
#include "EventStep.h"
#include "EventDetect.h"
#include "WorldManager.h"
#include "LogManager.h"

Cube::Cube(df::Vector position, int id) {
	h = NULL;
	this->setId(id);
	setSolidness(HARD);
	setType("Cube");
	setSprite("cube");
	setPosition(position);
	move_countdown = 0;
	move_slowdown = 5;
	registerInterest(df::STEP_EVENT);
	registerInterest(df::STEP_EVENT);
}
int Cube::eventHandler(const df::Event* p_e) {
	if (p_e->getType() == STEP_EVENT) {
		move_countdown--;
		if (move_countdown < 0) {
			move_countdown = 0;
		}
		if (h != NULL) {
			setPosition(h->getPosition() + Vector(0,-1));
		}
		//hacky collisions every frame
		WM.moveObject(this, getPosition());
	}
	if (p_e->getType() == df::COLLISION_EVENT) {
		const EventCollision* p_ec = dynamic_cast<const EventCollision*>(p_e);
		df::Vector hero_pos;
		if (p_ec->getObject1()->getType() == "Hero" && move_countdown == 0) {
			hero_pos == p_ec->getObject1()->getPosition();
		}
		else if (p_ec->getObject2()->getType() == "Hero" && move_countdown == 0) {
			hero_pos == p_ec->getObject2()->getPosition();
		}
		return 1;
	}
	return 0;
}	
void Cube::pickUp(Hero* h) {
	this->h = h;
	setSolidness(SPECTRAL);
	setAltitude(5);
}
void Cube::drop(df::Vector position) {
	h = NULL;
	setPosition(position);
	setSolidness(HARD);
}