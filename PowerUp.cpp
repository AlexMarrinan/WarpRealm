#include "PowerUp.h"
#include "EventView.h"
#include "Points.h"
#include "WorldManager.h"
#include "EventUnload.h"
#include "Hero.h"
#include "ResourceManager.h"

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
	switch (type) {
	case PORTALS:
		//df::Sound* p_sound = RM.getSound("equip-portals");
		//p_sound->play();		
		break;
	case SWORD:
		df::Sound* p_sound = RM.getSound("equip-sword");
		p_sound->play();		
		break;
	}
	EventUnload eu(this);
	WM.onEvent(&eu);
}