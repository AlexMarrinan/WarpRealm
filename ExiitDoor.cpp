#include "ExiitDoor.h"
#include "EventNuke.h"
#include "Points.h"
#include "EventView.h"
#include "EventUnload.h"
#include "WorldManager.h"
#include "Wall.h"
#include "HealthDisplay.h"
#include "OrbIcon.h"
#include "Room.h"

ExitDoor::ExitDoor(df::Vector positon, int id, int orbs, Room* room) {
	setSprite("exitdoor");
	setType("Exit Door");
	setPosition(positon);
	setSolidness(df::Solidness::HARD);
	setId(id);
	for (int i = 0; i < ORB_MAX_COUNT; i++) {
		spawnOrbCounters(i, (i+1 <= HealthDisplay::orbs), room);
	}
}

void ExitDoor::spawnOrbCounters(int orbNubmer, bool collected, Room* room) {
	OrbIcon* oi = new OrbIcon(getPosition() + df::Vector(9, 0) + df::Vector(3*(orbNubmer - 5), 0), collected);
	room->loaded.insert(oi);
}
void ExitDoor::getItem() {

}