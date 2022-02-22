#pragma once
#include "Object.h"
#include "Vector.h"
class Portal: public df::Object
{
private:
	bool isBlue; //true if blue, false if red?
public:
	Portal(df::Vector postion, Portal* old_portal, bool blue = true);
	bool isBluePortal() const;
}; 

