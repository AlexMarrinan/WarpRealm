#pragma once
#include "Item.h"
class LockedDoor: public Item
{
public:
	LockedDoor(df::Vector positon, bool isHorizontal, int id);
	void getItem();
};

