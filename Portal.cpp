#include "Portal.h"
#include "EventCollision.h"
#include "EventStep.h"
#include "WorldManager.h"
#include "LogManager.h"
#include "ResourceManager.h"

Portal::Portal(df::Vector pos, Portal* old_portal, bool blue, PortalDirection new_direction) {
	other_portal = NULL;
	direction = new_direction;
	setSolidness(df::Solidness::HARD);
	setPosition(pos);
	registerInterest(df::COLLISION_EVENT);
	registerInterest(df::STEP_EVENT);

;	setAltitude(0);
	setType("Portal");
	isBlue = blue;
	canUse = true;
	LM.writeLog("making portal");
	if (isBlue) {
		setSprite("blue-portal");
	}
	else {
		setSprite("red-portal");
	}
	df::Sound* p_sound = RM.getSound("blue-portal-open");
	p_sound->play();
	if (old_portal != NULL) {
		WM.markForDelete(old_portal);
	}
}
bool Portal::isBluePortal() const {
	return isBlue;
}

void Portal::setOtherPortal(Portal* op)
{
	other_portal = op;
}

Portal* Portal::getOtherPortal() const
{
	return other_portal;
}

PortalDirection Portal::getDirection() const
{
	return direction;
}

int Portal::eventHandler(const df::Event* p_e) {
	if (p_e->getType() == df::STEP_EVENT) {
		WM.moveObject(this, getPosition());
		return 1;
	}
	if (p_e->getType() == df::COLLISION_EVENT) {
		const df::EventCollision* ec = dynamic_cast<const df::EventCollision*>(p_e);
		if (ec->getObject1()->getType() == "Water" || ec->getObject2()->getType() == "Water") {
			canUse = false;
			unregisterInterest(df::STEP_EVENT);
		}
		return 1;
	}
	return 0;
}
