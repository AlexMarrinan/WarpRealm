#include "Door.h"
#include "EventButton.h"
#include "Wall.h"
#include "LogManager.h"
#include "WorldManager.h"
#include "EventUnload.h"

const df::Vector door_offset(0, 100);

Door::Door(df::Vector positon, int id, int button_id, int orientation) {
	setPosition(positon);
	original_pos = positon;
	setType("Door");
	setId(id);
	if (orientation == HORIZONTAL) {
		setSprite(WALL_DH_STR);
	}
	else if (orientation == VERTICAL) {
		setSprite(WALL_DV_STR);
	}
	this->button_id = button_id;
	registerInterest(BUTTON_EVENT);
	open = false;
}
void Door::getItem() {

}
int Door::eventHandler(const df::Event* p_e) {
	if (p_e->getType() == BUTTON_EVENT) {
		LM.writeLog("button event");
		

		const EventButton* eb = dynamic_cast<const EventButton*>(p_e);
		LM.writeLog("this id: %d", button_id);
		LM.writeLog("expected id: %d", eb->output_id);
		LM.writeLog("value: %d", eb->value);

		if (eb->output_id == this->button_id) {
			LM.writeLog("correct id!");
			if (eb->value == PRESSED) {
				open = true;
				setPosition(getPosition() + door_offset);
			}
			else if (eb->value == UNPRESSED) {
				open = false;
				setPosition(original_pos);
			}
			else if (eb->value == ARROW_PRESSED) {
				EventUnload eu(this);
				WM.onEvent(&eu);
			}
			return 1;
		}
	}
	return 0;
}