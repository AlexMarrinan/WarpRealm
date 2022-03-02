#include "HealthDisplay.h"
#include "WorldManager.h"
#include "EventDeath.h"

int HealthDisplay::orbs;

HealthDisplay::HealthDisplay() {
	setLocation(df::TOP_LEFT);
	setViewString(ORB_STRING);
	setColor(df::YELLOW);
	setBorder(false);
	setValue(ORB_COUNT);
	// Need to update score each second, so count "step" events.
	registerInterest(df::STEP_EVENT);
}

int HealthDisplay::eventHandler(const df::Event* p_e) {
	// Parent handles event if score update.
	if (df::ViewObject::eventHandler(p_e)) {
		return 1;
	}
	// If step, increment score every second (30 steps).
	if (p_e->getType() == df::STEP_EVENT) {
		/*if (dynamic_cast <const df::EventStep*> (p_e)
			->getStepCount() % 30 == 0)
			setValue(getValue() + 1);*/
		orbs = this->getValue();
		return 1;
	}
	// If get here, have ignored this event.
	return 0;
}
