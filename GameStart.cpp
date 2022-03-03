#include "GameStart.h"
#include "WorldManager.h"
#include "EventKeyboard.h"
#include "GameManager.h"
#include "Hero.h"
#include "Points.h"
#include "BigSaucer.h"
#include "ResourceManager.h"
#include "Music.h"
#include "LaserDisplay.h"
#include "HealthDisplay.h"

GameStart::GameStart() {
    setType("GameStartr");
    setSprite("gamestart");

    // Play start music.
    p_music = RM.getMusic("start music");
    //playMusic();

    // Set starting location in the middle of window.
    int world_horiz = (int)WM.getBoundary().getHorizontal();
    int world_vert = (int)WM.getBoundary().getVertical();
    df::Vector p(world_horiz / 2, world_vert / 2);
    setPosition(p);

    // Register for "keyboard" event.
    registerInterest(df::KEYBOARD_EVENT);
}

void GameStart::playMusic() {
    //p_music->play();
}

int GameStart::eventHandler(const df::Event* p_e) {
    if (p_e->getType() == df::KEYBOARD_EVENT) {
        df::EventKeyboard* p_keyboard_event = (df::EventKeyboard*)p_e;
        switch (p_keyboard_event->getKey()) {
        case df::Keyboard::P:// play
            start();
            break;
        case df::Keyboard::Q:// quit
            GM.setGameOver();
            break;
        default: // Key is not handled.
            break;
        }
        return 1;
    }

    // If get here, have ignored this event.
    return 0;
}

void GameStart::start() {

    Hero* hero = new Hero;

    Room* r0 = new Room("rooms/00.txt");

    Room* r1 = new Room("rooms/01.txt");
    r0->setNextRoom(r1, RoomDirection::UP);
    r1->setNextRoom(r0, RoomDirection::DOWN);
    Room* r2 = new Room("rooms/02.txt");
    r1->setNextRoom(r2, RoomDirection::UP);
    r2->setNextRoom(r1, RoomDirection::DOWN);
    Room* r3 = new Room("rooms/03.txt");
    r3->setNextRoom(r2, RoomDirection::LEFT);
    r2->setNextRoom(r3, RoomDirection::RIGHT);
    Room* r4 = new Room("rooms/04.txt");
    r3->setNextRoom(r4, RoomDirection::RIGHT);
    r4->setNextRoom(r3, RoomDirection::LEFT);
    Room* r5 = new Room("rooms/05.txt");
    r4->setNextRoom(r5, RoomDirection::RIGHT);
    r5->setNextRoom(r4, RoomDirection::LEFT);
    Room* r6 = new Room("rooms/06.txt");
    r3->setNextRoom(r6, RoomDirection::UP);
    r6->setNextRoom(r3, RoomDirection::DOWN);
    Room* r7 = new Room("rooms/07.txt");
    r6->setNextRoom(r7, RoomDirection::RIGHT);
    r7->setNextRoom(r6, RoomDirection::LEFT);
    Room* r8 = new Room("rooms/08.txt");
    r1->setNextRoom(r8, RoomDirection::RIGHT);
    r8->setNextRoom(r1, RoomDirection::LEFT);
    Room* r9 = new Room("rooms/09.txt");
    r8->setNextRoom(r9, RoomDirection::RIGHT);
    r9->setNextRoom(r8, RoomDirection::LEFT);
    Room* r10 = new Room("rooms/10.txt");
    r9->setNextRoom(r10, RoomDirection::UP);
    r10->setNextRoom(r9, RoomDirection::DOWN);
    Room* r11 = new Room("rooms/11.txt");
    r9->setNextRoom(r11, RoomDirection::RIGHT);
    r11->setNextRoom(r9, RoomDirection::LEFT);
    Room* r12 = new Room("rooms/12.txt");
    r11->setNextRoom(r12, RoomDirection::DOWN);
    r12->setNextRoom(r11, RoomDirection::UP);
    Room* r13 = new Room("rooms/13.txt");
    r12->setNextRoom(r13, RoomDirection::LEFT);
    r13->setNextRoom(r12, RoomDirection::RIGHT);
    Room* r14 = new Room("rooms/14.txt");
    r8->setNextRoom(r14, RoomDirection::DOWN);
    r14->setNextRoom(r8, RoomDirection::UP);
    Room* r15_2 = new Room("rooms/15.2.txt");
    r14->setNextRoom(r15_2, RoomDirection::LEFT);
    r15_2->setNextRoom(r14, RoomDirection::RIGHT);

    Room* r15 = new Room("rooms/15.txt");
    r1->setNextRoom(r15, RoomDirection::LEFT);
    r15->setNextRoom(r1, RoomDirection::RIGHT);
    Room* r16 = new Room("rooms/16.txt");
    r15->setNextRoom(r16, RoomDirection::LEFT);
    r16->setNextRoom(r15, RoomDirection::RIGHT);
    Room* r17 = new Room("rooms/17.txt");
    r16->setNextRoom(r17, RoomDirection::UP);
    r17->setNextRoom(r16, RoomDirection::DOWN);
    Room* r18 = new Room("rooms/18.txt");
    r17->setNextRoom(r18, RoomDirection::RIGHT);
    r18->setNextRoom(r17, RoomDirection::LEFT);
    Room* r19 = new Room("rooms/19.txt");
    r18->setNextRoom(r19, RoomDirection::DOWN);
    r19->setNextRoom(r18, RoomDirection::UP);
    Room* r20 = new Room("rooms/20.txt");
    r15->setNextRoom(r20, RoomDirection::DOWN);
    r20->setNextRoom(r15, RoomDirection::UP);
    Room* r21 = new Room("rooms/21.txt");
    r20->setNextRoom(r21, RoomDirection::LEFT);
    r21->setNextRoom(r20, RoomDirection::RIGHT);
    Room* r22 = new Room("rooms/22.txt");
    r20->setNextRoom(r22, RoomDirection::RIGHT);
    r22->setNextRoom(r20, RoomDirection::LEFT);

    //Room* rF = new Room("rooms/final.txt");
    //r2->setNextRoom(rF, RoomDirection::UP);
    //rF->setNextRoom(r2, RoomDirection::DOWN);
  
    r0->loadRoom();
    hero->currentRoom = r0;
    hero->startingRoom = r0;

    new Points;
    new HealthDisplay;

    // When game starts, become inactive.
    setActive(false);
}

int GameStart::draw() {
    return df::Object::draw();
}