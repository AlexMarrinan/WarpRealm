#pragma once
#include "Object.h"
#include "EventCollision.h"

class Saucer : public df::Object {

public:
    Saucer();
    ~Saucer();
    int eventHandler(const df::Event* p_e) override;
    void moveToStart();
    void out();
    void hit(const df::EventCollision* p_c);
};
