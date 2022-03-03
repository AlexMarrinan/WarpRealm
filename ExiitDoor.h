#pragma once
#include "Item.h"
#include "ObjectList.h"

class ExitDoor : public Item
{
private:
	int animation_countdown;
	bool opening;
public:
	df::ObjectList iconsList;
	ExitDoor(df::Vector positon, int id, int orbs, class Room* room);
	void getItem();
	void spawnOrbCounters(int orbNubmer, bool collected, class Room* room);
	int eventHandler(const df::Event* p_e);
;};

