#pragma once
#include "Object.h"
#include "Vector.h"
#include "Room.h"

class Portal: public df::Object
{
private:
	bool isBlue; //true if blue, false if red?
	Portal* other_portal;
	RoomDirection direction;
public:
	Portal(df::Vector postion, Portal* old_portal, bool blue, RoomDirection new_direction);
	bool isBluePortal() const;
	void setOtherPortal(Portal* op);
	Portal* getOtherPortal() const;
	RoomDirection getDirection() const;
}; 

