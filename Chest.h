#pragma once
#include "Item.h"

class Chest: public Item
{
public:
	Chest(df::Vector positon, int id);
	void getItem();
};

