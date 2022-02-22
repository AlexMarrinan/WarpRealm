#pragma once
#include "Object.h"
#include "Event.h"

enum ItemType {
	KEY = 0,
	LOCKED_DOOR = 1,
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
public:
	bool should_load;
	ItemContainer(ItemType type, df::Vector position, int id);
	ItemType getType() const;
	df::Vector getPosition() const;
	void setLoad(bool new_load = false);
	bool shouldLoad() const;
	int getId() const;
};

