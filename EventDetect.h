#pragma once
#include "Event.h"
#include "Hero.h"

const std::string DETECT_EVENT = "detect";

class EventDetect : public df::Event {

public:
    Hero* hero;
    EventDetect(Hero* h);
};

