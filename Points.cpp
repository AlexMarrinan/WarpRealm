#include "Points.h"
#include "EventDeath.h"
#include "WorldManager.h"

int Points::key_count;

Points::Points() {
	setLocation(df::TOP_RIGHT);
	setViewString(POINTS_STRING);
	setColor(df::YELLOW);
	setBorder(false);
	// Need to update score each second, so count "step" events.
	registerInterest(df::STEP_EVENT);
	registerInterest(DEATH_EVENT);
}

int Points::eventHandler(const df::Event* p_e) {
	// Parent handles event if score update.
	if (df::ViewObject::eventHandler(p_e)) {
		return 1;
	}
	// If step, increment score every second (30 steps).
	if (p_e->getType() == df::STEP_EVENT) {
		key_count = this->getValue();
		return 1;
	}
	if (p_e->getType() == DEATH_EVENT) {
		WM.markForDelete(this);
	}
	// If get here, have ignored this event.
	return 0;
}
