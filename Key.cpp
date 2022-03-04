#include "Key.h"
#include "EventView.h"
#include "Points.h"
#include "WorldManager.h"
#include "EventUnload.h"
#include "ResourceManager.h"

Key::Key(df::Vector positon, int id) {
	setSprite("key");
	setType("Key");
	setPosition(positon);
	setSolidness(df::Solidness::HARD);
	setId(id);
}

void Key::getItem() {
	df::Sound* p_sound = RM.getSound("keys");
	p_sound->play();
	df::EventView ev(POINTS_STRING, 1, true);
	WM.onEvent(&ev);
	EventUnload eu(this);
	WM.onEvent(&eu);
}