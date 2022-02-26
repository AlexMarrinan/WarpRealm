#pragma once
#include "Event.h"


const std::string DEATH_EVENT = "death";

class EventDeath : public df::Event {

public:
    EventDeath();
};