#pragma once
#include "Item.h"

class Cube: public Item
{
private:
	//int shoot_countdown;
	//int shoot_slowdown;
	class Hero* h;
	int move_countdown;
	int move_slowdown;
public:
	Cube(df::Vector position, int id);
	int eventHandler(const df::Event* p_e);
	void pickUp(class Hero* h);
	void drop(df::Vector position);
};

