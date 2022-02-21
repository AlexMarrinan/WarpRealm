#include "LogManager.h"
#include "WorldManager.h"
#include "ResourceManager.h"
#include "GameManager.h"
#include "EventStep.h"
#include "EventOut.h"
#include "Laser.h"


Laser::Laser(df::Vector hero_pos) {
	// Note: in Bullet constructor
	// Make the Bullets soft so can pass through Hero.
	setSolidness(df::SOFT);

	// Link to "ship" sprite.
	setSprite("laser");

	registerInterest(df::KEYBOARD_EVENT);
	registerInterest(df::STEP_EVENT);

	setType("Laser");
	// Set starting location, based on hero's position passed in.
	df::Vector p(hero_pos.getX() + 3, hero_pos.getY());
	setPosition(p);

	// Bullets move 5 space each game loop.
	// The direction is set when the Hero fires.
	setSpeed(5);
}