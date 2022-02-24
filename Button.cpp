#include "Button.h"
#include "LogManager.h"
#include "WorldManager.h"
#include "EventButton.h"

Button::Button(df::Vector positon, int id, int button_id) {
	setSprite("button-off");
	setType("Button");
	setPosition(positon);
	setSolidness(df::Solidness::SOFT);
	setAltitude(1);
	registerInterest(df::STEP_EVENT);
	registerInterest(df::COLLISION_EVENT);
	setId(id);
	slowdown = 4;
	countdown = 0;
	pressed = false;
	this->button_id = button_id;
}

void Button::getItem() {

}
int Button::eventHandler(const df::Event* p_e) {
	if (p_e->getType() == df::STEP_EVENT) {
		countdown--;
		if (countdown < 0) {
			countdown == 0;
			if (pressed) {
				pressed = false;
				EventButton eb(button_id, UNPRESSED);
				WM.onEvent(&eb);
			}
		}
		if (pressed) {
			setSprite("button-on");
		}
		else {
			setSprite("button-off");
		}
		return 1;
	}
	if (p_e->getType() == df::COLLISION_EVENT) {
		const df::EventCollision* p_ec = dynamic_cast<const df::EventCollision*>(p_e);
		if (p_ec->getObject1()->getType() == "Hero" ||
			p_ec->getObject2()->getType() == "Hero") {
			pressed = true;
			countdown = slowdown;
			EventButton eb(button_id, PRESSED);
			WM.onEvent(&eb);
		}
		return 1;
	}
	return 0;
}