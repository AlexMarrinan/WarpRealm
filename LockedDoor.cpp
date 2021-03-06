#include "LockedDoor.h"
#include "EventNuke.h"
#include "Points.h"
#include "EventView.h"
#include "EventUnload.h"
#include "WorldManager.h"
#include "Wall.h"

LockedDoor::LockedDoor(df::Vector positon, bool isHorizontal, int id) {
	if (isHorizontal){
		setSprite(WALL_DLH_STR);
	}
	else {
		setSprite(WALL_DLV_STR);
	}
	setType("Locked Door");
	setPosition(positon);
	setSolidness(df::Solidness::HARD);
	setId(id);
}

void LockedDoor::getItem() {
	if (Points::key_count > 0) {
		df::EventView ev(POINTS_STRING, -1, true);
		WM.onEvent(&ev);
		EventUnload eu(this);
		WM.onEvent(&eu);
	}
}