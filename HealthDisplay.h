#pragma once
#include "Object.h"
#include "ViewObject.h"
#include "Event.h"
#include "EventStep.h"

#define ORB_STRING "Orbs"
#define ORB_COUNT 0
#define ORB_MAX_COUNT 5

class HealthDisplay : public df::ViewObject {

public:
    HealthDisplay();
    static int orbs;
    int eventHandler(const df::Event* p_e) override;
};