#include "ResourceManager.h"
#include "WorldManager.h"
#include "LogManager.h"
#include "Saucer.h"
#include "EventOut.h"
#include "EventCollision.h"
#include "Explosion.h"
#include "GameManager.h"
#include "EventNuke.h"
#include "EventView.h"
#include "Points.h"
#include "game.h"
#define NORMAL_SPAWN_RATE 10

Saucer::Saucer() {
	// Setup "saucer" sprite.
	setSprite("saucer");

	// Set object type.
	setType("Saucer");

	// Set speed in horizontal direction.
	setVelocity(df::Vector(-0.25, 0)); // 1 space left every 4 frames

	registerInterest(NUKE_EVENT);

	// Set starting location in the middle of window.
	int world_horiz = (int)WM.getBoundary().getHorizontal();
	int world_vert = (int)WM.getBoundary().getVertical();
	df::Vector p(world_horiz / 2, world_vert / 2);
	moveToStart();
}
Saucer::~Saucer() {
	// Send "view" event with points to interested ViewObjects.
	// Add 10 points.
	df::EventView ev(POINTS_STRING, 10, true);
	WM.onEvent(&ev);
}
int Saucer::eventHandler(const df::Event* p_e) {

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

		// Saucers appear stay around perpetually.
		new Saucer;
		WM.markForDelete(this);
		return 1;
	}
	return 0;
}
void Saucer::out() {
	if (getPosition().getX() >= 0) {
		return;
	}
	moveToStart();
	// Spawn new Saucer to make the game get harder.
	spawnSaucer(NORMAL_SPAWN_RATE);
}

void Saucer::moveToStart() {
	df::Vector temp_pos;

	float world_horiz = WM.getBoundary().getHorizontal();
	float world_vert = WM.getBoundary().getVertical();

	// x is off right side of window
	temp_pos.setX(world_horiz + rand() % (int)world_horiz + 3.0f);

	// y is in vertical range
	temp_pos.setY(rand() % (int)(world_vert - 4) + 4.0f);

	// If collision, move right slightly until empty space.
	df::ObjectList collision_list = WM.getCollisions(this, temp_pos);
	while (!collision_list.isEmpty()) {
		temp_pos.setX(temp_pos.getX() + 1);
		collision_list = WM.getCollisions(this, temp_pos);
	}

	WM.moveObject(this, temp_pos);
}
void Saucer::hit(const df::EventCollision* p_c) {
	// If Saucer on Saucer, ignore.
	if ((p_c->getObject1()->getType() == "Saucer") &&
		(p_c->getObject2()->getType() == "Saucer"))
		return;
	// If Bullet...
	if ((p_c->getObject1()->getType() == "Bullet") || (p_c->getObject2()->getType() == "Bullet") || 
		(p_c->getObject1()->getType() == "Laser") || (p_c->getObject2()->getType() == "Laser")){

		// Create an explosion.
		Explosion* p_explosion = new Explosion;
		p_explosion->setPosition(this->getPosition());

		// Saucers appear stay around perpetually.
		spawnSaucer(NORMAL_SPAWN_RATE);

		// Play "explode" sound.
		df::Sound* p_sound = RM.getSound("explode");
		p_sound->play();
	}
	// If Hero, mark both objects for destruction.
	if (((p_c->getObject1()->getType()) == "Hero") ||
		((p_c->getObject2()->getType()) == "Hero")) {
		WM.markForDelete(p_c->getObject1());
		WM.markForDelete(p_c->getObject2());	
	}
}