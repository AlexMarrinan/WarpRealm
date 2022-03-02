#include "OrbIcon.h"

OrbIcon::OrbIcon(df::Vector position, bool collected) {
	setPosition(position);
	if (collected) {
		setSprite("orbicon-collected");
	}
	else {
		setSprite("orbicon");
	}
}
