#pragma once
#include "EventKeyboard.h"
#include "EventCollision.h"
#include "Reticle.h"
#include "EventMouse.h"
#include "Room.h"

class Hero : public df::Object {

private:
    Reticle* p_reticle;
    df::Vector tempLaserPos1;
    df::Vector tempLaserPos2;

    Portal* blue_portal;
    Portal* red_portal;

    int move_slowdown;
    int move_countdown;
    int fire_slowdown;
    int fire_countdown;
    int laser_slowdown;
    int laser_countdown;
    int nuke_count;
    int portal_slowdown;
    int portal_cooldown;


    void kbd(const df::EventKeyboard* p_keyboard_event);
    void mouse(const df::EventMouse* p_mouse_event);
    void move(float dx, float dy);
public:
    Room* currentRoom;
    Hero();
    ~Hero();
    int eventHandler(const df::Event* p_e) override;
    void step();
    void fire(df::Vector target, bool isBlue = true);
    void fire_laser(df::Vector target);
    void spawn_laser();
    int get_laser_charge();
    void nuke();
    void out();
    Portal* getPortal(bool isBlue = true) const;
    void setPortal(Portal* p, bool isBlue = true);
    void handleCollisions(const EventCollision* p_ec);
    void usePortal(Portal* p);
};