#include "Turret.h"
#include "Arrow.h"
#include "EventDetect.h"
#include "EventStep.h"
#include "LogManager.h"

Turret::Turret(df::Vector position) {
	h = NULL;
	shoot_slowdown = 30;
	shoot_countdown = 0;
	setSolidness(HARD);
	setType("Turret");
	setSprite("turret");
	setPosition(position);
	registerInterest(DETECT_EVENT);
	registerInterest(df::STEP_EVENT);
}
int Turret::eventHandler(const df::Event* p_e) {
	if (p_e->getType() == STEP_EVENT) {
		shoot_countdown--;
		if (shoot_countdown < 0) {
			shoot_countdown = 0;
		}
	}
	if (p_e->getType() == DETECT_EVENT && shoot_countdown == 0) {
		LM.writeLog("in detect for turret");
		if (h == NULL) {
			const EventDetect* p_ed = dynamic_cast<const EventDetect*>(p_e);
			h = p_ed->hero;
		}
		int x = getPosition().getX();
		int y = getPosition().getY();
		int h_x = h->getPosition().getX();
		int h_y = h->getPosition().getY();
		
		if (h_x > x && h_y < y + 4 && h_y > y - 4) {
			fire(Vector(2, 0));
		}
		else if (h_x < x && h_y < y + 2 && h_y > y - 4) {
			fire(Vector(-2, 0));
		}
		else if (h_y > y && h_x < x + 5 && h_x > x - 5) {
			fire(Vector(0, 1));
		}
		else if (h_y < y && h_x < x + 5 && h_x > x - 5) {
			fire(Vector(0, -1));
		}
		return 1;
	}
	return 0;
}
void Turret::fire(df::Vector direction) {
	new Arrow(direction, getPosition() + direction);
	shoot_countdown = shoot_slowdown;
}