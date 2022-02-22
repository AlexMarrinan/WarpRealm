#include "Key.h"
#include "EventView.h"
#include "Points.h"
#include "WorldManager.h"
#include "EventUnload.h"

Key::Key(df::Vector positon, int id) {
	setSprite("key");
	setType("Key");
	setPosition(positon);
	setSolidness(df::Solidness::HARD);
	setId(id);
}

void Key::getItem() {
	df::EventView ev(POINTS_STRING, 1, true);
	WM.onEvent(&ev);
	EventUnload eu(this);
	WM.onEvent(&eu);
}