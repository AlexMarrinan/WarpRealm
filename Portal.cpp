#include "Portal.h"
#include "WorldManager.h"
#include "LogManager.h"
#include "ResourceManager.h"

Portal::Portal(df::Vector pos, Portal* old_portal, bool blue, PortalDirection new_direction) {
	other_portal = NULL;
	direction = new_direction;
	setSolidness(df::Solidness::HARD);
	setPosition(pos);
	setAltitude(0);
	setType("Portal");
	isBlue = blue;
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
