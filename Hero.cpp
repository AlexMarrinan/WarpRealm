#include "LogManager.h"
#include "WorldManager.h"
#include "ResourceManager.h"
#include "GameManager.h"
#include "Hero.h"
#include "EventStep.h"
#include "EventMouse.h"
#include "EventNuke.h"
#include "EventDetect.h"
#include "Laser.h"
#include "LaserDisplay.h"
#include "EventView.h"
#include "GameOver.h"
#include "Line.h"
#include "DisplayManager.h"
#include "Points.h"
#include "EventOut.h"
#include "Key.h"
#include "LockedDoor.h"
#include "EventUnload.h"
#include "Enemy.h"
#include "HealthDisplay.h"
#include "Cube.h"
#include "Sword.h"

#define X_AMOUNT 1
#define Y_AMOUNT 0.5

Hero::Hero() {
	// Link to "ship" sprite.
	setSprite("hero-up");
	direction = RoomDirection::UP;

	registerInterest(df::KEYBOARD_EVENT);
	registerInterest(df::STEP_EVENT);
	registerInterest(df::MSE_EVENT);
	registerInterest(UNLOAD_EVENT);

	setType("Hero");
	df::Vector p(10, WM.getBoundary().getVertical() / 2 + 2);
	setPosition(p);

	// Create reticle for firing bullets.
	p_reticle = new Reticle();
	p_reticle->draw();

	move_slowdown = 1;
	move_countdown = move_slowdown;
	fire_slowdown = 10;
	fire_countdown = fire_slowdown;
	portal_slowdown = 15;
	portal_cooldown = 0;
	sword_slowdown = 15;
	sword_cooldown = 0;
	tempLaserPos1 = df::Vector(-100, -100);
	tempLaserPos2 = df::Vector(-100, -100);

	hasPortalGun = false;
	hasSword = false;

	blue_portal = NULL;
	red_portal = NULL;

	cube_held = NULL;
}

Hero::~Hero() {
	// Create GameOver object.
	// Shake screen (severity 20 pixels x&y, duration 10 frames).
	DM.shake(20, 20, 10);

	new GameOver;

	// Mark Reticle for deletion.
	WM.markForDelete(p_reticle);
	// Make a big explosion with particles.
	df::addParticles(df::SPARKS, getPosition(), 2, df::BLUE);
	df::addParticles(df::SPARKS, getPosition(), 2, df::YELLOW);
	df::addParticles(df::SPARKS, getPosition(), 3, df::RED);
	df::addParticles(df::SPARKS, getPosition(), 3, df::RED);
}

int Hero::eventHandler(const df::Event * p_e) {
	if (p_e->getType() == df::KEYBOARD_EVENT) {
		const df::EventKeyboard* p_keyboard_event =
			dynamic_cast <const df::EventKeyboard*> (p_e);
		kbd(p_keyboard_event);

		return 1;
	}
	if (p_e->getType() == df::OUT_EVENT) {
		//TODO: MOVE PLAYER TO NEW ROOM WHEN THEY STEP OOB
		out();
		return 1;
	}
		//if left mouse press, fire bullet
	if (p_e->getType() == df::MSE_EVENT) {
		const df::EventMouse* p_mouse_event =
			dynamic_cast <const df::EventMouse*> (p_e);
		mouse(p_mouse_event);
		return 1;
	}
	//call step every in game step
	if (p_e->getType() == df::STEP_EVENT) {
		step();
		return 1;
	}
	if (p_e->getType() == COLLISION_EVENT) {
		handleCollisions(dynamic_cast<const EventCollision*>(p_e));
		return 1;
	}
	if (p_e->getType() == UNLOAD_EVENT) {
		const EventUnload* p_event_unload = (dynamic_cast<const EventUnload*>(p_e));
		Item* item = p_event_unload->item_to_unload;
		currentRoom->markItemUnload(item->getId());
		if (item->getType() == "Button") {
			return 1;
		}
		LM.writeLog("item id: %d", item->getId());
		WM.markForDelete(item);
		currentRoom->removeObject(item);
		return 1;
	}
	return 0;
}

// Take appropriate action according to key pressed.
void Hero::kbd(const df::EventKeyboard* p_keyboard_event) {
	df::Keyboard::Key k = p_keyboard_event->getKey();
	float x = 0;
	float y = 0;
	if (k == df::Keyboard::W) { //up
		if (p_keyboard_event->getKeyboardAction() == df::KEY_DOWN) {
			y = -Y_AMOUNT;
			direction = RoomDirection::UP;
			setSprite("hero-up");
		}
	}
	if (k == df::Keyboard::S) { //down
		if (p_keyboard_event->getKeyboardAction() == df::KEY_DOWN) {
			direction = RoomDirection::DOWN;
			setSprite("hero-down");
			y = +Y_AMOUNT;
		}
	}
	if (k == df::Keyboard::A) { //left
		if (p_keyboard_event->getKeyboardAction() == df::KEY_DOWN) {
			direction = RoomDirection::LEFT;
			setSprite("hero-left");
			x = -X_AMOUNT;
		}
	}
	if (k == df::Keyboard::D) { //right
		if (p_keyboard_event->getKeyboardAction() == df::KEY_DOWN) {
			direction = RoomDirection::RIGHT;
			setSprite("hero-right");
			x = +X_AMOUNT;
		}
	}
	move(x, y);
	if (k == df::Keyboard::ESCAPE) { //quit
		if (p_keyboard_event->getKeyboardAction() == df::KEY_PRESSED)
			GM.setGameOver();
			//WM.markForDelete(this);
	}
	if (k == df::Keyboard::SPACE) { //attack or drop cube
		if (p_keyboard_event->getKeyboardAction() == df::KEY_PRESSED) {
			if (cube_held != NULL) {
				dropCube();
			}
			else {
				attack();
			}
		}
	}
}
void Hero::mouse(const df::EventMouse* p_mouse_event) {
	// Pressed button?
	if ((p_mouse_event->getMouseAction() == df::CLICKED) &&
		(p_mouse_event->getMouseButton() == df::Mouse::LEFT))
		fire(p_mouse_event->getMousePosition());
	if ((p_mouse_event->getMouseAction() == df::CLICKED) &&
		(p_mouse_event->getMouseButton() == df::Mouse::RIGHT))
		fire(p_mouse_event->getMousePosition(), false);
}
void Hero::move(float dx, float dy) {
	// See if time to move.
	if (move_countdown > 0)
		return;
	move_countdown = move_slowdown;

	df::Vector new_pos(getPosition().getX() + dx, getPosition().getY() + dy);
	WM.moveObject(this, new_pos);
	return;

	// If stays on window, allow move.
	if ((new_pos.getX() > 3) &&
		(new_pos.getX() < WM.getBoundary().getHorizontal()) &&
		(new_pos.getY() > 3) &&
		(new_pos.getY() < WM.getBoundary().getVertical() - 1))
		return;
}
void Hero::step() {
	//Detect Event
	EventDetect ed(this);
	WM.onEvent(&ed);

	// Move countdown.
	move_countdown--;
	if (move_countdown < 0)
		move_countdown = 0;
	// Fire countdown.
	fire_countdown--;
	if (fire_countdown < 0)
		fire_countdown = 0;
	portal_cooldown--;
	if (portal_cooldown < 0) {
		if (red_portal != NULL && blue_portal != NULL) {
			red_portal->setSolidness(HARD);
			blue_portal->setSolidness(HARD);
		}
		portal_cooldown = 0;
	}
	sword_cooldown--;
	if (sword_cooldown < 0)
		sword_cooldown = 0;
	//STUPID HACKY WAY TO ALLWAYS CHECK COLLISIONS
	//TODO: maybe make less shit
	WM.moveObject(this, getPosition());
}
void Hero::out() {
	Room* r;
	Vector v;
	if (getPosition().getY() < 0 && currentRoom->getNextRoom(RoomDirection::UP) != NULL) {
		r = currentRoom->getNextRoom(RoomDirection::UP);
		v = Vector(getPosition().getX(), WM.getBoundary().getVertical() - 4);
	}
	else if (getPosition().getY() > WM.getBoundary().getVertical() && 
		currentRoom->getNextRoom(RoomDirection::DOWN) != NULL) {
		r = currentRoom->getNextRoom(RoomDirection::DOWN);
		v = Vector(getPosition().getX(), 2);
	}
	else if (getPosition().getX() < 0 && currentRoom->getNextRoom(RoomDirection::LEFT) != NULL) {
		r = currentRoom->getNextRoom(RoomDirection::LEFT);
		v = Vector(WM.getBoundary().getHorizontal() - 4, getPosition().getY());
	}
	else if (getPosition().getX() > WM.getBoundary().getHorizontal() &&
		currentRoom->getNextRoom(RoomDirection::RIGHT) != NULL) {
		r = currentRoom->getNextRoom(RoomDirection::RIGHT);
		v = Vector(2, getPosition().getY());
	}
	else {
		return;
	}
	currentRoom->unloadRoom();
	r->loadRoom();
	WM.markForDelete(blue_portal);
	blue_portal = NULL;
	WM.markForDelete(red_portal);
	red_portal = NULL;
	cube_held = NULL;
	currentRoom = r;
	setPosition(v);
}
void Hero::fire(df::Vector target, bool isBlue) {
	if (fire_countdown > 0 || !hasPortalGun)
		return;
	fire_countdown = fire_slowdown;
	// Fire Laser towards target.
	// Compute normalized vector to position, then scale by speed (1).
	df::Vector v = target - getPosition();
	v.normalize();
	v.scale(1.5);
	Bullet* p = new Bullet(this, isBlue);
	p->setVelocity(v);

	// Play "fire" sound.
	df::Sound* p_sound = RM.getSound("fire");
	p_sound->play();
}
void Hero::attack() {
	if (sword_cooldown == 0 && hasSword) {
		sword_cooldown = sword_slowdown;
		new Sword(this, this->direction);
	}
}
Portal* Hero::getPortal(bool isBlue) const {
	return isBlue ? blue_portal : red_portal;
}
void Hero::setPortal(Portal* new_portal, bool isBlue) {
	if (isBlue) {
		blue_portal = new_portal;
	}
	else {
		red_portal = new_portal;
	}
}
void Hero::handleCollisions(const EventCollision* p_ec) {
	//Object* p_o;
	if (p_ec->getObject1()->getType() == "Portal") {
		LM.writeLog("hitting portal");
		usePortal(dynamic_cast<Portal*>(p_ec->getObject1()));
	}
	else if (p_ec->getObject2()->getType() == "Portal") {
		LM.writeLog("hitting portal");
		usePortal(dynamic_cast<Portal*>(p_ec->getObject2()));
	}
	else if (p_ec->getObject1()->getType() == "PowerUp") {
		getPowerUp(dynamic_cast<PowerUp*>(p_ec->getObject1())->type);
	}
	else if (p_ec->getObject2()->getType() == "PowerUp") {
		getPowerUp(dynamic_cast<PowerUp*>(p_ec->getObject2())->type);
	}
	else if (p_ec->getObject1()->getType() == "Enemy" || (p_ec->getObject1()->getType() == "Arrow")) {
		Enemy* e = dynamic_cast<Enemy*>(p_ec->getObject1());
		df::EventView ev(HEALTH_STRING, -e->getDamage() , true);
		WM.onEvent(&ev);
	}
	else if (p_ec->getObject2()->getType() == "Enemy" || (p_ec->getObject1()->getType() == "Arrow")) {
		Enemy* e = dynamic_cast<Enemy*>(p_ec->getObject2());
		df::EventView ev(HEALTH_STRING, -e->getDamage(), true);
		WM.onEvent(&ev);
	}
	else if (p_ec->getObject1()->getType() == "Cube") {
		Cube* c = dynamic_cast<Cube*>(p_ec->getObject1());
		cube_held = c;
		c->pickUp(this);
	}
	else if (p_ec->getObject2()->getType() == "Cube") {
		Cube* c = dynamic_cast<Cube*>(p_ec->getObject2());
		cube_held = c;
		c->pickUp(this);
	}
	return;
}

void Hero::usePortal(Portal* p) {
	LM.writeLog("using portal");
	if (portal_cooldown <= 0) {
		portal_cooldown = portal_slowdown;
		if (p->isBluePortal() && red_portal != NULL) {
			LM.writeLog("blue");
			this->setPosition(red_portal->getPosition());
			red_portal->setSolidness(SOFT);
		}
		else if (!p->isBluePortal() && blue_portal != NULL){
			LM.writeLog("red");
			this->setPosition(blue_portal->getPosition());
			blue_portal->setSolidness(SOFT);
		}
	}
}
bool Hero::intersectsObject(Object* obj) {
	df::Box A = this->getBox();
	df::Box B = obj->getBox();
	float Ax1 = A.getCorner().getX();
	float Bx1 = B.getCorner().getX();
	float Ax2 = A.getCorner().getX() + A.getHorizontal();
	float Bx2 = B.getCorner().getX() + B.getHorizontal();
	//writeMessage("ax1: %f bx1: %f ax2: %f bx2:%f\n", Ax1, Bx1, Ax2, Bx2);
	bool x_overlap = (Bx1 <= Ax1 && Ax1 <= Bx2) || (Ax1 <= Bx1 && Bx1 <= Ax2);

	float Ay1 = A.getCorner().getY();
	float By1 = B.getCorner().getY();
	float Ay2 = A.getCorner().getY() + A.getVertical();
	float By2 = B.getCorner().getY() + B.getVertical();
	//writeMessage("ay1: %f by1: %f ay2: %f by2:%f\n\n", Ay1, By1, Ay2, By2);
	bool y_overlap = (By1 <= Ay1 && Ay1 <= By2) || (Ay1 <= By1 && By1 <= Ay2);

	return (x_overlap && y_overlap);
}

void Hero::getPowerUp(PowerUpType type) {
	switch (type) {
	case PORTALS:
		hasPortalGun = true;
		break;
	case SWORD:
		hasSword = true;
		break;
	}
}

void Hero::dropCube() {
	df::Vector offset;
	switch (this->direction) {
	case RoomDirection::UP:
		offset = Vector(0, -2.5);
		break;
	case RoomDirection::DOWN:
		offset = Vector(0, 2.5);
		break;
	case RoomDirection::LEFT:
		offset = Vector(-4, 0);
		break;
	case RoomDirection::RIGHT:
		offset = Vector(4, 0);
		break;
	}
	
	cube_held->drop(getPosition() + offset);
	ItemContainer* ic = currentRoom->getItemContainer(cube_held->getId());
	ic->setPosition(cube_held->getPosition());
	cube_held = NULL;
}