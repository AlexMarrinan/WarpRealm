#pragma once
#include "EventCollision.h"
#include "Hero.h"

class Bullet : public df::Object {

private:
    void out();
    void hit(const df::EventCollision* p_collision_event);
    bool isBlue;
public:
    Bullet();
    Bullet(Hero* hero_pos, bool isBlue = true);
    Hero* p_hero;
    int eventHandler(const df::Event* p_e) override;
};