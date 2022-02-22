#include "Portal.h"
#include "WorldManager.h"
#include "LogManager.h"

Portal::Portal(df::Vector pos, Portal* old_portal, bool blue) {
	setSolidness(df::Solidness::SOFT);
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
	if (old_portal != NULL) {
		WM.markForDelete(old_portal);
	}
}
bool Portal::isBluePortal() const {
	return isBlue;
}