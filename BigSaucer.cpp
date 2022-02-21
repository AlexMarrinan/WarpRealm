#include "ResourceManager.h"
#include "WorldManager.h"
#include "LogManager.h"
#include "EventOut.h"
#include "EventCollision.h"
#include "Explosion.h"
#include "GameManager.h"
#include "EventNuke.h"
#include "EventView.h"
#include "EventStep.h"
#include "Points.h"
#include "BigSaucer.h"
#include "game.h"
#define BIG_SPAWN_RATE 20

BigSaucer::BigSaucer() {
	//Set health to 4.
	health = 4;

	//set up damage cooldown 
	dmg_slowdown = 15;
	dmg_countdown = dmg_slowdown;

	// Setup "bigsaucer" sprite.
	setSprite("bigsaucer4");

	// Set object type.
	setType("BigSaucer");

	// Set speed in horizontal direction.
	setVelocity(df::Vector(-0.17, 0)); // 1 space left every 4 frames

	registerInterest(NUKE_EVENT);
	registerInterest(df::STEP_EVENT);

	// Set starting location in the middle of window.
	int world_horiz = (int)WM.getBoundary().getHorizontal();
	int world_vert = (int)WM.getBoundary().getVertical();
	df::Vector p(world_horiz / 2, world_vert / 2);
	moveToStart();
}
BigSaucer::~BigSaucer() {
	// Send "view" event with points to interested ViewObjects.
	// Add 50 points.
	df::EventView ev(POINTS_STRING, 50, true);
	WM.onEvent(&ev);
}
int BigSaucer::eventHandler(const df::Event* p_e) {

	if (p_e->getType() == df::OUT_EVENT) {
		out();
		return 1;
	}
	if (p_e->getType() == df::COLLISION_EVENT) {
		const df::EventCollision* p_collision_event =
			dynamic_cast <const df::EventCollision*> (p_e);
		hit(p_collision_event);
		return 1;
	}
	if (p_e->getType() == NUKE_EVENT) {
		// Create an explosion.
		Explosion* p_explosion = new Explosion;
		p_explosion->setPosition(this->getPosition());

		WM.markForDelete(this);
		return 1;
	}
	//call step every in game step
	if (p_e->getType() == df::STEP_EVENT) {
		// Damage countdown.
		dmg_countdown--;
		if (dmg_countdown < 0)
			dmg_countdown = 0;
		return 1;
	}
	return 0;
}

void BigSaucer::hit(const df::EventCollision* p_c) {
	// If Saucer on Saucer, ignore.
	if ((p_c->getObject1()->getType() == "Saucer") &&
		(p_c->getObject2()->getType() == "Saucer"))
		return;
	// If Bullet...
	if (p_c->getObject1()->getType() == "Bullet"){
		WM.markForDelete(p_c->getObject1());
		lowerHealth();
		return;
	}
	if (p_c->getObject2()->getType() == "Bullet") {
		WM.markForDelete(p_c->getObject2());
		lowerHealth();
		return;
	}
	// If Laser ...
	if ((p_c->getObject1()->getType() == "Laser") || 
		(p_c->getObject2()->getType() == "Laser") ) {
		lowerHealth();
		return;
	}

	// If Hero, mark both objects for destruction.
	if (((p_c->getObject1()->getType()) == "Hero") ||
		((p_c->getObject2()->getType()) == "Hero")) {
		WM.markForDelete(p_c->getObject1());
		WM.markForDelete(p_c->getObject2());
	}
}
void BigSaucer::out() {
	if (getPosition().getX() >= 0) {
		return;
	}
	moveToStart();
	// Spawn new Saucer to make the game get harder.
	spawnSaucer(BIG_SPAWN_RATE);
}
void BigSaucer::lowerHealth() {
	if (dmg_countdown > 0) {
		return;
	}
	dmg_countdown = dmg_slowdown;
	health--;

	// Play "explode" sound.
	df::Sound* p_sound = RM.getSound("explode");
	p_sound->play();

	switch (health) {
	case 3: setSprite("bigsaucer3");
		break;
	case 2: setSprite("bigsaucer2");
		break;
	case 1: setSprite("bigsaucer1");
		break;
	case 0:
		// Create an explosion.
		Explosion* p_explosion = new Explosion;
		p_explosion->setPosition(this->getPosition());

		// Saucers appear stay around perpetually.
		spawnSaucer(BIG_SPAWN_RATE);

		WM.markForDelete(this);
		break;
	}
}