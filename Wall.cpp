#include "Wall.h"

Wall::Wall(WallType type, Vector pos, bool portals) {
	portals_work = portals;
	setType("Wall");
	setPosition(pos);
	setSolidness(HARD);
	setWallType(type);
}
void Wall::setWallType(WallType type) {
	this->type = type;
	switch (type) {
	case H_1:
		if (portals_work) {
			setSprite(WALL_H1_STR_P);
		}
		else {
			setSprite(WALL_H1_STR);
		}
		break;
	case V_1:
		if (portals_work) {
			setSprite(WALL_V1_STR_P);
		}
		else {
			setSprite(WALL_V1_STR);
		}
		break;
	case N_1:
		if (portals_work) {
			setSprite(WALL_N1_STR_P);
		}
		else {
			setSprite(WALL_N1_STR);
		}
		break;
	case WATER:
		setType("Water");
		setSprite(WALL_WATER_STR);
		setAltitude(0);
		break;
	case FIZZLER:
		setType("Fizzler");
		setSolidness(SOFT);
		setAltitude(0);
		setSprite(WALL_FIZZLER_STR);
		break;
	}
}
WallType Wall::getWallType() const {
	return type;
}
bool Wall::isPortalable() const {
	return portals_work;
}

WallContainer::WallContainer(WallType type, Vector pos, bool portals) {
	this->type = type;
	this->position = pos;
	this->portals_work = portals;
}
WallType WallContainer::getType() const{
	return type;
}
Vector WallContainer::getPosition() const {
	return position;
}
bool WallContainer::isPoralable() const {
	return portals_work;
}