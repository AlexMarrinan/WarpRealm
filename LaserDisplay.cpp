#include "LaserDisplay.h"

LaserDisplay::LaserDisplay() {
	setLocation(df::TOP_CENTER);
	setViewString(LASERDISPLAY_STRING);
	setColor(df::YELLOW);

	// Need to update score each second, so count "step" events.
	registerInterest(df::STEP_EVENT);
}

int LaserDisplay::eventHandler(const df::Event* p_e) {
	// Parent handles event if score update.
	if (df::ViewObject::eventHandler(p_e)) {
		return 1;
	}
	// If get here, have ignored this event.
	return 0;
}
