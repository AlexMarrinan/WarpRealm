#pragma once
#include "Item.h"
#include "Button.h"


#define HORIZONTAL 1
#define VERTICAL 2

class Door : public Item
{
private:
	int button_id;
	df::Vector original_pos;
public:
	bool open;
	Door(df::Vector positon, int id, int button_id, int orientation);
	void getItem();
	int eventHandler(const df::Event* p_e) override;
};

