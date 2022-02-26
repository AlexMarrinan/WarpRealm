#pragma once
#include "Object.h"
#include "ViewObject.h"
#include "Event.h"
#include "EventStep.h"

#define HEALTH_STRING "Health"
#define MAX_HEALTH 20

class HealthDisplay : public df::ViewObject {

public:
    HealthDisplay();
    static int hp;
    int eventHandler(const df::Event* p_e) override;
};