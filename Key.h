#pragma once
#include "Item.h"

class Key: public Item
{
public:
	Key(df::Vector position, int id);
	void getItem() override;
};

