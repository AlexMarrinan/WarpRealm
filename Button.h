#pragma once
#include "Item.h"
#include "EventStep.h"
#include "EventCollision.h"
#include "Hero.h"

#define ARROW_PRESSED 2
#define PRESSED 1
#define UNPRESSED 0

class Button : public Item
{
private: 
	int button_id;
public:
	int countdown;
	int slowdown;
	Button(df::Vector positon, int id, int button_id, bool arrow_pressed);
	void getItem();
	int eventHandler(const df::Event* p_e) override;
	bool pressed;
	bool arrow_pressed;
};
