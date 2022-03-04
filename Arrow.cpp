#include "Arrow.h"
#include "EventCollision.h"
#include "LogManager.h"
#include "WorldManager.h"
#include "Hero.h"
#include "ResourceManager.h"

Arrow::Arrow(df::Vector direction, df::Vector pos, Room* room) {
	//red_portal = Hero::getPortal(false);
	//blue_portal = Hero.getPortal(true);
	setPosition(pos);
	setDirection(direction);
	if (direction.getX() == 2) {
		setSprite("arrow-r");
		setSpeed(0.25);
	}
	else if (direction.getX() == -2) {
		setSprite("arrow-l");
		setSpeed(0.25);
	}
	else if (direction.getY() == 1) {
		setSprite("arrow-d");
		setSpeed(0.125);
	}
	else if (direction.getY() == -1) {
		setSprite("arrow-u");
		setSpeed(0.25);
	}
	this->room = room;
	room->loaded.insert(this);
	setType("Arrow");
	setSolidness(SOFT);
	df::Sound* p_sound = RM.getSound("arrow-shoot");
	p_sound->play();
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
		else if (p_ec->getObject1()->getType() == "Hero" || p_ec->getObject2()->getType() == "Hero") {
			return 0;
		}
		else if (p_ec->getObject1()->getType() == "Arrow" && p_ec->getObject2()->getType() == "Arrow") {
			return 0;
		}
		room->loaded.remove(this);
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
			nd.setXY(-2, 0);
			offset.setXY(-5, 0);
		}
		else if (pd == R) {
			nd.setXY(2, 0);
			offset.setXY(5, 0);
		}
		new Arrow(nd, p->getOtherPortal()->getPosition() + offset, this->room);
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
			nd.setXY(-2, 0);
			offset.setXY(-5, 0);
		}
		else if (pd == R) {
			nd.setXY(2, 0);
			offset.setXY(5, 0);
		}
		new Arrow(nd, p->getOtherPortal()->getPosition() + offset, this->room);
		p->getOtherPortal()->setSolidness(SOFT);
	}
}