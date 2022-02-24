#include "EventDetect.h"

EventDetect::EventDetect(Hero* h) {
	setType(DETECT_EVENT);
	this->hero = h;
}