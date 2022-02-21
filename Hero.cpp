#include "LogManager.h"
#include "WorldManager.h"
#include "ResourceManager.h"
#include "GameManager.h"
#include "Hero.h"
#include "EventStep.h"
#include "EventMouse.h"
#include "EventNuke.h"
#include "Laser.h"
#include "LaserDisplay.h"
#include "EventView.h"
#include "GameOver.h"
#include "Line.h"
#include "DisplayManager.h"
#include "Points.h"
#include "EventOut.h"

#define X_AMOUNT 1
#define Y_AMOUNT 0.5

Hero::Hero() {
	// Link to "ship" sprite.
	setSprite("ship");

	registerInterest(df::KEYBOARD_EVENT);
	registerInterest(df::STEP_EVENT);
	registerInterest(df::MSE_EVENT);

	setType("Hero");
	df::Vector p(10, WM.getBoundary().getVertical() / 2 + 2);
	setPosition(p);

	// Create reticle for firing bullets.
	p_reticle = new Reticle();
	p_reticle->draw();

	move_slowdown = 2;
	move_countdown = move_slowdown;
	fire_slowdown = 15;
	fire_countdown = fire_slowdown;
	laser_slowdown = 100;
	laser_countdown = 0;
	nuke_count = 1;

	tempLaserPos1 = df::Vector(-100, -100);
	tempLaserPos2 = df::Vector(-100, -100);
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
	return 0;
}

// Take appropriate action according to key pressed.
void Hero::kbd(const df::EventKeyboard* p_keyboard_event) {
	df::Keyboard::Key k = p_keyboard_event->getKey();
	float x = 0;
	float y = 0;
	if (k == df::Keyboard::W) { //up
		if (p_keyboard_event->getKeyboardAction() == df::KEY_DOWN)
			y = -Y_AMOUNT;
	}
	if (k == df::Keyboard::S) { //down
		if (p_keyboard_event->getKeyboardAction() == df::KEY_DOWN)
			y = +Y_AMOUNT;
	}
	if (k == df::Keyboard::A) { //left
		if (p_keyboard_event->getKeyboardAction() == df::KEY_DOWN)
			x = -X_AMOUNT;
	}
	if (k == df::Keyboard::D) { //right
		if (p_keyboard_event->getKeyboardAction() == df::KEY_DOWN)
			x = +X_AMOUNT;
	}
	move(x, y);
	if (k == df::Keyboard::ESCAPE) { //quit
		if (p_keyboard_event->getKeyboardAction() == df::KEY_PRESSED)
			WM.markForDelete(this);
	}
	if (k == df::Keyboard::SPACE) { //space
		if (p_keyboard_event->getKeyboardAction() == df::KEY_PRESSED)
			nuke();
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
	// Move countdown.
	move_countdown--;
	if (move_countdown < 0)
		move_countdown = 0;
	// Fire countdown.
	fire_countdown--;
	if (fire_countdown < 0)
		fire_countdown = 0;
	// Laser countdown.
	laser_countdown--;
	if (laser_countdown < 0) {
		laser_countdown = 0;
	}
	df::EventView ev(LASERDISPLAY_STRING, get_laser_charge(), false);
	WM.onEvent(&ev);
	//if laser countdown is in first 10 frames, spawn a new laser projectile
	if (laser_countdown <= laser_slowdown && laser_countdown >= laser_slowdown - 10) {
		spawn_laser();
	}
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
		v = Vector(WM.getBoundary().getHorizontal() - 4, getPosition().getX());
	}
	else if (getPosition().getX() > WM.getBoundary().getHorizontal() &&
		currentRoom->getNextRoom(RoomDirection::RIGHT) != NULL) {
		r = currentRoom->getNextRoom(RoomDirection::RIGHT);
		v = Vector(2, getPosition().getX());
	}
	else {
		return;
	}
	currentRoom->unloadRoom();
	r->loadRoom();
	currentRoom = r;
	setPosition(v);
}
void Hero::fire(df::Vector target, bool isBlue) {
	if (fire_countdown > 0)
		return;
	fire_countdown = fire_slowdown;
	// Fire Laser towards target.
	// Compute normalized vector to position, then scale by speed (1).
	df::Vector v = target - getPosition();
	v.normalize();
	v.scale(1);
	Bullet* p = new Bullet(getPosition(), isBlue);
	p->setVelocity(v);

	// Play "fire" sound.
	df::Sound* p_sound = RM.getSound("fire");
	p_sound->play();
}
void Hero::fire_laser(df::Vector target) {
	if (laser_countdown > 0)
		return;
	laser_countdown = laser_slowdown;
	// Fire Laser Toward Target
	// Compute normalized vector to position, then scale by speed (1).
	df::Vector v = target - getPosition();
	v.normalize();
	v.scale(5);

	tempLaserPos1 = getPosition();
	tempLaserPos2 = v;

	// Play "fire" sound.
	df::Sound* p_sound = RM.getSound("fire");
	p_sound->play();
}
void Hero::spawn_laser() {
	Laser* l = new Laser(tempLaserPos1);
	l->setVelocity(tempLaserPos2);
}
void Hero::nuke() {
	// Check if nukes left.
	if (!nuke_count)
		return;
	nuke_count--;
	// Create "nuke" event and send to interested Objects.
	EventNuke nuke;
	WM.onEvent(&nuke);
	// Send "view" event with nukes to interested ViewObjects.
	df::EventView ev("Nukes", -1, true);
	WM.onEvent(&ev);

	//Shake the screen
	DM.shake(10, 10, 5);

	// Play "nuke" sound.
	df::Sound* p_sound = RM.getSound("nuke");
	p_sound->play();
}
int Hero::get_laser_charge() {
	return abs(laser_countdown - laser_slowdown);
}