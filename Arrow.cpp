#include "Arrow.h"
#include "EventCollision.h"
#include "LogManager.h"
#include "WorldManager.h"
#include "Hero.h"

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
		else if (p_ec->getObject1()->getType() == "Water" || p_ec->getObject2()->getType() == "Water") {
			return 0;
		}
		else if (p_ec->getObject1()->getType() == "Fizzler" || p_ec->getObject2()->getType() == "Fizzler") {
			return 0;
		}
		WM.markForDelete(this);
		return 1;
	}
	return 0;
}

void Arrow::usePortal(Portal* p)
{
	LM.writeLog("arrow using portal");
	//if (portal_cooldown <= 0) {
	//	portal_cooldown = portal_slowdown;
	if (p->isBluePortal() && p->getOtherPortal() != NULL) {
		LM.writeLog("blue");
		//this->setPosition(p->getOtherPortal()->getPosition() + Vector(3, 0));
		PortalDirection pd = p->getOtherPortal()->getDirection();
		Vector offset;
		Vector nd;
		if (pd == D) {
			nd.setXY(0, -1);
			offset.setXY(0, -3);
		}
		else if (pd == U) {
			nd.setXY(0, 1);
			offset.setXY(0, 3);
		}
		else if (pd == L) {
			nd.setXY(-1, 0);
			offset.setXY(-5, 0);
		}
		else if (pd == R) {
			nd.setXY(1, 0);
			offset.setXY(5, 0);
		}
		new Arrow(nd, p->getOtherPortal()->getPosition() + offset);
		p->getOtherPortal()->setSolidness(SOFT);
	}
	else if (!p->isBluePortal() && p->getOtherPortal() != NULL) {
		LM.writeLog("red");
		//this->setPosition(p->getOtherPortal()->getPosition()+Vector(3,0));
		PortalDirection pd = p->getOtherPortal()->getDirection();
		Vector offset;
		Vector nd;
		if (pd == D) {
			nd.setXY(0, -1);
			offset.setXY(0, -3);
		}
		else if (pd == U) {
			nd.setXY(0, 1);
			offset.setXY(0, 3);
		}
		else if (pd == L) {
			nd.setXY(-1, 0);
			offset.setXY(-5, 0);
		}
		else if (pd == R) {
			nd.setXY(1, 0);
			offset.setXY(5, 0);
		}
		new Arrow(nd, p->getOtherPortal()->getPosition() + offset);
		p->getOtherPortal()->setSolidness(SOFT);
	}
}