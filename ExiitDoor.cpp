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
#include "LogManager.h"
#include "EventCollision.h";
#include "GameOver.h"
#include "EventDeath.h"

ExitDoor::ExitDoor(df::Vector positon, int id, int orbs, Room* room) {
	setSprite("exitdoor");
	setType("Exit Door");
	setPosition(positon);
	setSolidness(df::Solidness::HARD);
	setId(id);
	for (int i = 0; i < ORB_MAX_COUNT; i++) {
		spawnOrbCounters(i, (i+1 <= HealthDisplay::orbs), room);
	}
	registerInterest(df::COLLISION_EVENT);
	registerInterest(df::STEP_EVENT);
	animation_countdown = 0;
	opening = false;
}

void ExitDoor::spawnOrbCounters(int orbNubmer, bool collected, Room* room) {
	OrbIcon* oi = new OrbIcon(getPosition() + df::Vector(9, 0) + df::Vector(3*(orbNubmer - 5), 0), collected);
	this->iconsList.insert(oi);
	room->loaded.insert(oi);
}
void ExitDoor::getItem() {
	if (HealthDisplay::orbs >= ORB_MAX_COUNT) {
		opening = true;
		EventDeath ed;
		WM.onEvent(&ed);
	}
}

int ExitDoor::eventHandler(const df::Event* p_e) {
	if (opening && p_e->getType() == df::STEP_EVENT && opening) {
		LM.writeLog("Starting exit door animation %d\n", animation_countdown);
		animation_countdown++;
		if (animation_countdown == 5) {
			WM.markForDelete(iconsList);
			setSprite("animated-exitdoor");
		}
		else if (animation_countdown == 110) {
			EventUnload eu(this);
			WM.onEvent(&eu);
			new GameOver;
		}
		return 1;
	}
	if (p_e->getType() == df::COLLISION_EVENT) {
		const df::EventCollision* p_ec = dynamic_cast<const df::EventCollision*>(p_e);
		if (p_ec->getObject1()->getType() == "Hero" ||
			p_ec->getObject2()->getType() == "Hero") {
			getItem();
		}
		return 1;
	}
	return 0;
}
