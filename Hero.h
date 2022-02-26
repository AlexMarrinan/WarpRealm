#pragma once
#include "EventKeyboard.h"
#include "EventCollision.h"
#include "Reticle.h"
#include "EventMouse.h"
#include "Room.h"
#include "Cube.h"
#include "PowerUp.h"

class Hero : public df::Object {

private:
    Reticle* p_reticle;
    df::Vector tempLaserPos1;
    df::Vector tempLaserPos2;

    int move_slowdown;
    int move_countdown;
    int fire_slowdown;
    int fire_countdown;
    int portal_slowdown;
    int portal_cooldown;
    int sword_slowdown;
    int sword_cooldown;
    int damage_slowdown;
    int damage_cooldown;
    int death_cooldown;

    bool hasPortalGun;
    bool hasSword;
    bool dead;
    
    Portal* blue_portal;
    Portal* red_portal;
    Cube* cube_held;
    RoomDirection direction;
    void kbd(const df::EventKeyboard* p_keyboard_event);
    void mouse(const df::EventMouse* p_mouse_event);
    void move(float dx, float dy);
public:
    Room* currentRoom;
    Room* startingRoom;
    Hero();
    ~Hero();
    int eventHandler(const df::Event* p_e) override;
    void step();
    void fire(df::Vector target, bool isBlue = true);
    void attack();
    void out();
    Portal* getPortal(bool isBlue = true) const;
    void setPortal(Portal* p, bool isBlue = true);
    void handleCollisions(const EventCollision* p_ec);
    void usePortal(Portal* p);
    bool intersectsObject(Object* i);
    void getPowerUp(PowerUpType type);
    void dropCube();
    void death();
};