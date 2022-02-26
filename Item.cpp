#include "Item.h"
#include "EventCollision.h"

Item::Item() {

}
Item::Item(int id) {
	id = id;
}
void Item::setId(int new_id) {
	id = new_id;
}
int Item::getId() const {
	return id;
}
void Item::getItem() {

}
int Item::eventHandler(const df::Event* p_e) {
	if (p_e->getType() == df::COLLISION_EVENT) {
		const df::EventCollision* p_ec = dynamic_cast<const df::EventCollision*>(p_e);
		if (p_ec->getObject1()->getType() == "Hero" ||
			p_ec->getObject2()->getType() == "Hero") {
			getItem();
		}
		return 1;
	}
	return 0;
}

ItemContainer::ItemContainer(ItemType type, df::Vector pos, int id) {
	this->type = type;
	this->position = pos;
	this->should_load = true;
	this->id = id;
	this->button_id = -1;
	this->activated = false;
	this->powerup_type = UNDEFINED;
}
ItemContainer::ItemContainer(ItemType type, df::Vector pos, int id, int button_id) {
	this->type = type;
	this->position = pos;
	this->should_load = true;
	this->id = id;
	this->button_id = button_id;
	this->activated = false;
	this->powerup_type = UNDEFINED;
}
ItemContainer::ItemContainer(ItemType type, df::Vector pos, int id, PowerUpType powerup_type) {
	this->type = type;
	this->position = pos;
	this->should_load = true;
	this->id = id;
	this->button_id = -1;
	this->activated = false;
	this->powerup_type = powerup_type;
}
ItemType ItemContainer::getType() const {
	return type;
}
df::Vector ItemContainer::getPosition() const {
	return position;
}
void ItemContainer::setPosition(df::Vector new_pos) {
	position = new_pos;
}
bool ItemContainer::shouldLoad() const {
	return should_load;
}
void ItemContainer::setLoad(bool new_load) {
	should_load = new_load;
}
int ItemContainer::getId() const {
	return id;
}
int ItemContainer::getButtonId() const {
	return button_id;
}
PowerUpType ItemContainer::getPowerUpType() const {
	return powerup_type;
}