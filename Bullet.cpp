#include "LogManager.h"
#include "WorldManager.h"
#include "ResourceManager.h"
#include "GameManager.h"
#include "Bullet.h"
#include "EventStep.h"
#include "EventOut.h"
#include "Wall.h"
#include "Portal.h"
#include "Hero.h"

Bullet::Bullet() {

}
Bullet::Bullet(Hero* hero, bool isBlue) {
	// Note: in Bullet constructor
	// Make the Bullets soft so can pass through Hero.
	setSolidness(df::SOFT);
	this->p_hero = hero;
	df::Vector hero_pos = hero->getPosition();

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
	setSpeed(5);
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
	else if (p_collision_event->getObject1()->getType() == "Door" || p_collision_event->getObject2()->getType() == "Door") {
		WM.markForDelete(this);
		return;
	}
	else {
		return;
	}
	Wall* w = dynamic_cast<Wall*>(p_o);
	WallType wt = w->getWallType();
	if (w->isPortalable()) {
		LM.writeLog("Hit portal surface!");
		Vector portal_offset = getVelocity();
		PortalDirection WD;
		//portal_offset.normalize();
		//portal_offset.scale(2);
		if (wt == H_1) {
			if (this->getPosition().getY() > w->getPosition().getY()) {
				WD = PortalDirection::U;
			}
			else {
				WD = PortalDirection::D;
			}
		}
		else if (wt == V_1) {
			if (this->getPosition().getX() > w->getPosition().getX()) {
				WD = PortalDirection::R;
			}
			else {
				WD = PortalDirection::L;
			}
		}
		else {
			WM.markForDelete(this);
			return;
		}
		Portal* p = new Portal(getPosition()-portal_offset, p_hero->getPortal(isBlue), this->isBlue, WD);
		p_hero->setPortal(p, isBlue);
		p->setOtherPortal(p_hero->getPortal(!isBlue));
		if (p_hero->getPortal(!isBlue) != NULL) {
			p_hero->getPortal(!isBlue)->setOtherPortal(p);
		}
	}
	WM.markForDelete(this);
}