#include "Chest.h"
#include "EventNuke.h"
#include "Points.h"
#include "EventView.h"
#include "EventUnload.h"
#include "WorldManager.h"
#include "HealthDisplay.h"
#include "Wall.h"

Chest::Chest(df::Vector positon, int id) {
	setSprite("chest");
	setType("Chest");
	setPosition(positon);
	setSolidness(df::Solidness::HARD);
	setId(id);
}

void Chest::getItem() {
	df::EventView ev2(ORB_STRING, +1, true);
	WM.onEvent(&ev2);
	EventUnload eu(this);
	WM.onEvent(&eu);
}