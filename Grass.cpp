#include "Grass.h"
#include "EventCollision.h"
#include "WorldManager.h"
#include "EventDetect.h"
#include "EventUnload.h"
#include "Room.h"
#include "ResourceManager.h"

Grass::Grass(df::Vector position, int id) {
	setType("Enemy");
	setSprite("breakable");
	setPosition(position);
	setHealth(1);
	setDamage(0);
	setId(id);
	registerInterest(df::COLLISION_EVENT);
}
int Grass::eventHandler(const df::Event* p_e) {
	if (p_e->getType() == df::COLLISION_EVENT) {
		//LM.writeLog("Enemy hit");
		const df::EventCollision* ec = dynamic_cast<const df::EventCollision*>(p_e);
		//LM.writeLog("%s", ec->getObject1()->getType().c_str());
		//LM.writeLog("%s", ec->getObject2()->getType().c_str());
		if ((ec->getObject1()->getType() == "Sword" || ec->getObject2()->getType() == "Sword") && damage_cooldown == 0) {
			df::Sound* p_sound = RM.getSound("breakable");
			p_sound->play();
			EventUnload eu(this);
			WM.onEvent(&eu);
		}
		return 1;
	}
	return Enemy::eventHandler(p_e);
}

