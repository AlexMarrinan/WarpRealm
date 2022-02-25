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
	if (Points::key_count > 0) {
		df::EventView ev(POINTS_STRING, -1, true);
		WM.onEvent(&ev);
		df::EventView ev2(HEALTH_STRING, +5, true);
		WM.onEvent(&ev2);
		EventUnload eu(this);
		WM.onEvent(&eu);
	}
}