#include "Arrow.h"
#include "EventCollision.h"
#include "LogManager.h"
#include "WorldManager.h"
#include "Hero.h"

void Arrow::usePortal(Portal* p)
{
	LM.writeLog("arrow using portal");
	//if (portal_cooldown <= 0) {
	//	portal_cooldown = portal_slowdown;
	if (p->isBluePortal() && p->getOtherPortal() != NULL) {
		LM.writeLog("blue");
		//this->setPosition(p->getOtherPortal()->getPosition() + Vector(3, 0));
		new Arrow(this->getDirection(), p->getOtherPortal()->getPosition() + Vector(5, 0));
		p->getOtherPortal()->setSolidness(SOFT);
	}
	else if (!p->isBluePortal() && p->getOtherPortal() != NULL) {
		LM.writeLog("red");
		//this->setPosition(p->getOtherPortal()->getPosition()+Vector(3,0));
		new Arrow(this->getDirection(), p->getOtherPortal()->getPosition() + Vector(5, 0));
		p->getOtherPortal()->setSolidness(SOFT);
	}
}

Arrow::Arrow(df::Vector direction, df::Vector pos) {
	//red_portal = Hero::getPortal(false);
	//blue_portal = Hero.getPortal(true);
	setPosition(pos);
	setDirection(direction);
	if (getDirection().getX() == 0) {
		setSprite("arrow-v");
		setSpeed(0.4);
	}
	else {
		setSprite("arrow-h");
		setSpeed(0.6);
	}
	setType("Arrow");
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
			if (p_ec->getObject1()->getType() == "Portal") {
		LM.writeLog("hitting portal");
		usePortal(dynamic_cast<Portal*>(p_ec->getObject1()));
	}
	else if (p_ec->getObject2()->getType() == "Portal") {
		LM.writeLog("hitting portal");
		usePortal(dynamic_cast<Portal*>(p_ec->getObject2()));
	}
		WM.markForDelete(this);
		return 1;
	}
	return 0;
}
