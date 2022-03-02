#pragma once
#include "Item.h"

class ExitDoor : public Item
{
public:
	ExitDoor(df::Vector positon, int id, int orbs, class Room* room);
	void getItem();
	void spawnOrbCounters(int orbNubmer, bool collected, class Room* room);
;};

