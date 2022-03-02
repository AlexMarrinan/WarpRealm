#pragma once
#include "Object.h"
#include "Vector.h"

enum PortalDirection {
	U = 1,
	D = 2,
	L,
	R,
};
class Portal: public df::Object
{
private:
	bool isBlue; //true if blue, false if red?
	Portal* other_portal;
	PortalDirection direction;
public:
	bool canUse;
	Portal(df::Vector postion, Portal* old_portal, bool blue, PortalDirection new_direction);
	bool isBluePortal() const;
	void setOtherPortal(Portal* op);
	Portal* getOtherPortal() const;
	PortalDirection getDirection() const;
	int eventHandler(const df::Event* p_e) override;
}; 

