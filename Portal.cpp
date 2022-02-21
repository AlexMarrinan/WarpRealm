#include "Portal.h"

Portal::Portal(df::Vector pos, bool blue) {
	setSolidness(df::Solidness::SOFT);
	setPosition(pos);
	setAltitude(0);
	isBlue = blue;
	if (isBlue) {
		setSprite("blue-portal");
	}
	else {
		setSprite("red-portal");
	}
}