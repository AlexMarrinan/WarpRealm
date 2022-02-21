#include "LogManager.h"
#include "WorldManager.h"
#include "ResourceManager.h"
#include "GameManager.h"
#include "Bullet.h"
#include "EventStep.h"
#include "EventOut.h"
#include "Wall.h"
#include "Portal.h"

Bullet::Bullet() {

}
Bullet::Bullet(df::Vector hero_pos, bool isBlue) {
	// Note: in Bullet constructor
	// Make the Bullets soft so can pass through Hero.
	setSolidness(df::SOFT);

	this->isBlue = isBlue;
	// Link to "ship" sprite.
	if (isBlue) {
		setSprite("bullet");
	}
	else {
		setSprite("red-bullet");
	}

	registerInterest(df::KEYBOARD_EVENT);
	registerInterest(df::STEP_EVENT);

	setType("Bullet");
	// Set starting location, based on hero's position passed in.
	df::Vector p(hero_pos.getX() + 3, hero_pos.getY());
	setPosition(p);

	// Bullets move 1 space each game loop.
	// The direction is set when the Hero fires.
	setSpeed(1);
}

int Bullet::eventHandler(const df::Event* p_e) {

	if (p_e->getType() == df::OUT_EVENT) {
		out();
		return 1;
	}
	if (p_e->getType() == df::COLLISION_EVENT) {
		const df::EventCollision* p_collision_event =
			dynamic_cast <const df::EventCollision*> (p_e);
		hit(p_collision_event);
		return 1;
	}
	return 0;
}

// If Bullet moves outside world, mark self for deletion.
void Bullet::out() {
	WM.markForDelete(this);
}

// If Bullet hits Saucer, mark Saucer and Bullet for deletion.
void Bullet::hit(const df::EventCollision* p_collision_event) {
	Object* p_o;
	if (p_collision_event->getObject1()->getType() == "Wall") {
		p_o = p_collision_event->getObject1();
	}
	else if (p_collision_event->getObject2()->getType() == "Wall") {
		p_o = p_collision_event->getObject2();
	}
	else {
		return;
	}
	Wall* w = dynamic_cast<Wall*>(p_o);
	if (w->isPortalable()) {
		//TODO: SPAWN PORTAL;
		LM.writeLog("Hit portal surface!");
		new Portal(getPosition(), this->isBlue);
	}
	WM.markForDelete(this);
}