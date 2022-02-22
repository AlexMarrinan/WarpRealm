#pragma once
#include "Item.h"
class LockedDoor: public Item
{
public:
	LockedDoor(df::Vector positon, int id);
	void getItem();
};

