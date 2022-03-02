#pragma once
#include "Object.h"
#include "Event.h"

enum ItemType {
	KEY = 0,
	LOCKED_DOOR_H = 1,
	LOCKED_DOOR_V,
	TURRET,
	BUTTON,
	DOOR_H,
	DOOR_V,
	CUBE,
	CHEST,
	POWERUP,
	MONSTER,
	BREAKABLE,
};
enum PowerUpType {
	UNDEFINED = -1,
	PORTALS = 0,
	SWORD,
	HEART,
	SECRET
};
class Item : public df::Object
{
private:
	int id;
public:
	Item();
	Item(int id);
	int eventHandler(const df::Event* p_e);
	virtual void getItem();
	void setId(int new_id);
	int getId() const;
};

class ItemContainer {
private:
	ItemType type;
	df::Vector position;
	int id;
	int button_id;
	PowerUpType powerup_type;
public:
	bool activated;
	bool should_load;
	ItemContainer(ItemType type, df::Vector position, int id);
	ItemContainer(ItemType type, df::Vector position, int id, int button_id);
	ItemContainer(ItemType type, df::Vector position, int id, PowerUpType powerup_type);

	ItemType getType() const;
	df::Vector getPosition() const;
	void setPosition(df::Vector new_pos);
	void setLoad(bool new_load = false);
	bool shouldLoad() const;
	int getId() const;
	int getButtonId() const;
	PowerUpType getPowerUpType() const;
};


