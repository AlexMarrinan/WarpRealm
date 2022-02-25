#include "PowerUp.h"
#include "EventView.h"
#include "Points.h"
#include "WorldManager.h"
#include "EventUnload.h"
#include "Hero.h"

PowerUp::PowerUp(df::Vector positon, int id, PowerUpType type) {
	setType("PowerUp");
	this->type = type;

	switch (type) {
	case PORTALS: 
		setSprite("pu-portals");
		break;
	case SWORD:
		setSprite("pu-sword");
		break;
	}
	setPosition(positon);
	setSolidness(df::Solidness::HARD);
	setId(id);
}

void PowerUp::getItem() {
	EventUnload eu(this);
	WM.onEvent(&eu);
}